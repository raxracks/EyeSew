#include "Script.hpp"

std::atomic_bool running = true;

Script::Script(Instance *game, Instance *workspace, Instance *script,
               std::string code) {
  running = true;

  m_Thread = std::thread([=]() {
    lua_State *L = luaL_newstate();
    if (luau_codegen_supported())
      luau_codegen_create(L);

    luaL_openlibs(L);
    Userdata(L).RegisterUserdata();

    Instance::Lua(L, game);
    lua_setglobal(L, "game");

    Instance::Lua(L, workspace);
    lua_setglobal(L, "workspace");

    // state.set_function(
    //     "wait",
    //     sol::overload(
    //         []() {
    //           std::this_thread::sleep_for(std::chrono::milliseconds(30));
    //           return true;
    //         },
    //         [](float length) {
    //           std::this_thread::sleep_for(
    //               std::chrono::seconds(static_cast<long long>(length)));
    //           return true;
    //         }));

    // lua_sethook(
    //     L,
    //     [](lua_State *L, lua_Debug *ar) {
    //       if (ar->event == LUA_HOOKLINE &&!running)
    //         luaL_error(L, "Stop execution");
    //     },
    //     LUA_MASKLINE, 0);

    size_t bytecodeSize;
    char *bytecode =
        luau_compile(code.c_str(), code.length(), nullptr, &bytecodeSize);

    if (luau_load(L, script->Name.c_str(), bytecode, bytecodeSize, 0) ==
        LUA_OK) {
      if (luau_codegen_supported())
        luau_codegen_compile(L, -1);
      if (lua_pcall(L, 0, 0, 0) != LUA_OK)
        std::cout << lua_tostring(L, -1) << std::endl;
    } else
      std::cout << lua_tostring(L, -1) << std::endl;
  });
  m_Thread.detach();
}

Script::~Script() {
  /*running = false;
  if (m_Thread.joinable())
      m_Thread.join();
  m_Thread.~thread();*/
}
