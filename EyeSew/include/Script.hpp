#pragma once
#include "Instance.hpp"
#include <thread>

class Script {
public:
    Script(Instance* game, Instance* workspace, Instance* script, std::string code);
    ~Script();

private:
    std::thread m_Thread;
};
