#include "Script.hpp"
#include "Usertypes.hpp"

//std::atomic_bool running = true;

Script::Script(Instance* game, Instance* workspace, Instance* script, std::string code)
{
    /*running = true;

    m_Thread = std::thread([=]() {
        sol::state state;
        Usertypes(state).RegisterUsertypes();
        state.open_libraries(sol::lib::base, sol::lib::math);
        state.set("game", game);
        state.set("workspace", workspace);
        state.set_panic([](lua_State* L) { return -1; });
        state.set("script", script);
        state.set_function("wait",
            sol::overload(
                []() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    return true;
                },
                [](float length) {
                    std::this_thread::sleep_for(std::chrono::seconds(static_cast<long long>(length)));
                    return true;
                }));

        lua_sethook(
            state.lua_state(), [](lua_State* L, lua_Debug* ar) {
                if (ar->event == LUA_HOOKLINE && !running)
                    luaL_error(L, "Stop execution");
            },
            LUA_MASKLINE, 0);

        try {
            state.safe_script(code);
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    });
    m_Thread.detach();*/
}

Script::~Script()
{
    /*running = false;
    if (m_Thread.joinable())
        m_Thread.join();
    m_Thread.~thread();*/
}
