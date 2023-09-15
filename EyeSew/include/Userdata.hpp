#pragma once

#include "Color3.hpp"
#include "Helpers.hpp"
#include "Instance.hpp"
#include "Vec3.hpp"
#include <iostream>
#include <lua.h>
#include <lualib.h>

class Userdata {
public:
  Userdata(lua_State *state) : m_State(state){};

  void RegisterUserdata();

private:
  lua_State *m_State;
};
