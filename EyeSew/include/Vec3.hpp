#pragma once
#include "Helpers.hpp"
#include <iostream>
#include <lua.h>
#include <lualib.h>
#include <raylib.h>
#include <string>

class Vec3 {
public:
  Vec3();
  Vec3(float X, float Y, float Z);

  operator Vector3() { return Vector3{X, Y, Z}; }

  float X;
  float Y;
  float Z;

  static void Metatable(lua_State *L);
  static void Lua(lua_State *L, Vec3 *vec3);
  static int __index(lua_State *L);
  static int __newindex(lua_State *L);
};
