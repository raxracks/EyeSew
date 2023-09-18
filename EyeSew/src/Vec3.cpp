#include "Vec3.hpp"

Vec3::Vec3() {
  X = 0.0f;
  Y = 0.0f;
  Z = 0.0f;
}

Vec3::Vec3(float X, float Y, float Z) {
  this->X = X;
  this->Y = Y;
  this->Z = Z;
}

void Vec3::Metatable(lua_State *L) {
  luaL_newmetatable(L, "Vector3");
  lua_pushstring(L, "__index");
  pushfunction(L, Vec3::__index);
  lua_settable(L, -3);
  lua_pushstring(L, "__newindex");
  pushfunction(L, Vec3::__newindex);
  lua_settable(L, -3);
}

void Vec3::Lua(lua_State *L, Vec3 *vec3) {
  Vec3 **pVec3 = (Vec3 **)lua_newuserdata(L, sizeof(Vec3 *));
  *pVec3 = vec3;

  luaL_getmetatable(L, "Vector3");
  lua_setmetatable(L, -2);
}

int Vec3::__index(lua_State *L) {
  Vec3 *self = GetSelf<Vec3>(L);
  std::string key = lua_tostring(L, 2);
  if (key == "X")
    lua_pushnumber(L, self->X);
  else if (key == "Y")
    lua_pushnumber(L, self->Y);
  else if (key == "Z")
    lua_pushnumber(L, self->Z);
  else
    lua_pushnil(L);

  return 1;
}

int Vec3::__newindex(lua_State *L) {
  Vec3 *self = GetSelf<Vec3>(L);
  std::string key = lua_tostring(L, 2);
  if (key == "X")
    self->X = lua_tonumber(L, 3);
  else if (key == "Y")
    self->Y = lua_tonumber(L, 3);
  else if (key == "Z")
    self->Z = lua_tonumber(L, 3);
  else
    luaL_error(L, "Cannot write property \"%s\" on Vector3: does not exist!",
               key.c_str());

  return 0;
}