#pragma once
#include "Helpers.hpp"
#include <cstdint>
#include <lua.h>
#include <lualib.h>
#include <raylib.h>
#include <string>

class Color3 {
public:
  Color3();
  Color3(float red, float green, float blue);
  Color3(float red, float green, float blue, float alpha);

  operator Color() {
    return Color{
        static_cast<uint8_t>(R * 255.0f), static_cast<uint8_t>(G * 255.0f),
        static_cast<uint8_t>(B * 255.0f), static_cast<uint8_t>(A * 255.0f)};
  }

  float R;
  float G;
  float B;
  float A;

  static void Metatable(lua_State *L);
  static void Lua(lua_State *L, Color3 *color3);
  static int __index(lua_State *L);
  static int __newindex(lua_State *L);
};
