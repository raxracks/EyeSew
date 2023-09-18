#include "Color3.hpp"

Color3::Color3() {
  R = 0;
  G = 0;
  B = 0;
  A = 1.0f;
}

Color3::Color3(float red, float green, float blue) {
  R = red;
  G = green;
  B = blue;
  A = 1.0f;
}

Color3::Color3(float red, float green, float blue, float alpha) {
  R = red;
  G = green;
  B = blue;
  A = alpha;
}

void Color3::Metatable(lua_State *L) {
  luaL_newmetatable(L, "Color3");
  lua_pushstring(L, "__index");
  pushfunction(L, Color3::__index);
  lua_settable(L, -3);
  lua_pushstring(L, "__newindex");
  pushfunction(L, Color3::__newindex);
  lua_settable(L, -3);
}

void Color3::Lua(lua_State *L, Color3 *color3) {
  Color3 **pColor3 = (Color3 **)lua_newuserdata(L, sizeof(Color3 *));
  *pColor3 = color3;

  luaL_getmetatable(L, "Color3");
  lua_setmetatable(L, -2);
}

int Color3::__index(lua_State *L) {
  Color3 *self = GetSelf<Color3>(L);
  std::string key = lua_tostring(L, 2);
  if (key == "R")
    lua_pushnumber(L, self->R);
  else if (key == "G")
    lua_pushnumber(L, self->G);
  else if (key == "B")
    lua_pushnumber(L, self->B);
  else if (key == "A")
    lua_pushnumber(L, self->A);
  else
    lua_pushnil(L);

  return 1;
}

int Color3::__newindex(lua_State *L) {
  Color3 *self = GetSelf<Color3>(L);
  std::string key = lua_tostring(L, 2);
  if (key == "R")
    self->R = lua_tonumber(L, 3);
  else if (key == "G")
    self->G = lua_tonumber(L, 3);
  else if (key == "B")
    self->B = lua_tonumber(L, 3);
  else if (key == "A")
    self->A = lua_tonumber(L, 3);
  else
    luaL_error(L, "Cannot write property \"%s\" on Color3: does not exist!",
               key.c_str());

  return 0;
}