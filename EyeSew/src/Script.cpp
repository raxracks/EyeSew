#include "Script.hpp"

Script::Script(Instance *game, Instance *workspace, Instance *script,
               std::string code) {
  m_Thread = std::thread([game, workspace, script, code, this]() {
    L = luaL_newstate();
    bool codegenSupported = luau_codegen_supported();

    if (codegenSupported)
      luau_codegen_create(L);

    luaL_openlibs(L);
    Userdata(L).RegisterUserdata();

    Instance::Lua(L, game);
    lua_setglobal(L, "game");

    Instance::Lua(L, workspace);
    lua_setglobal(L, "workspace");

    pushfunction(L, [](lua_State *L) {
      switch (lua_gettop(L)) {
      case 0:
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        break;
      case 1:
        std::this_thread::sleep_for(std::chrono::milliseconds(
            static_cast<int64_t>(lua_tonumber(L, 1) * 1000)));
        break;
      }

      lua_pushboolean(L, true);

      return 1;
    });
    lua_setglobal(L, "wait");

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

    size_t bytecodeSize;
    char *bytecode =
        luau_compile(code.c_str(), code.length(), nullptr, &bytecodeSize);
    if (luau_load(L, script->Name.c_str(), bytecode, bytecodeSize, 0) ==
        LUA_OK) {
      if (codegenSupported)
        luau_codegen_compile(L, -1);
      if (lua_pcall(L, 0, 0, 0) != LUA_OK)
        std::cout << lua_tostring(L, -1) << std::endl;
    } else
      std::cout << lua_tostring(L, -1) << std::endl;
  });
  m_Thread.detach();
}

Script::~Script() {
  // luaL_error(L, "Stop execution");
  // if (m_Thread.joinable())
  // m_Thread.join();
  // m_Thread.~thread();
}
