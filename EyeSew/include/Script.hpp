#pragma once
#include "Instance.hpp"
#include "Userdata.hpp"
#include <iostream>
#include <lua.h>
#include <luacode.h>
#include <luacodegen.h>
#include <luaconf.h>
#include <lualib.h>
#include <thread>

class Script {
public:
  Script(Instance *game, Instance *workspace, Instance *script,
         std::string code);
  ~Script();

private:
  std::thread m_Thread;
  lua_State *L;
};
