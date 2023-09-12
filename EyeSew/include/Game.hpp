#pragma once
#include "Instance.hpp"
#include "Script.hpp"

class Game {
public:
    Game();

    void Run();
    void Stop();

    Instance* game;
    Instance* gameClone;
    Instance* workspace;
    Instance* camera;
    bool running = false;

private:
    std::vector<Script*> m_Scripts;
};
