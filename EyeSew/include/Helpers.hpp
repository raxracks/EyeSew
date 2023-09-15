#pragma once
#include <lua.h>
#include <lualib.h>
#include <vector>

#define pushfunction(L, fn) lua_pushcfunction(L, fn, #fn)

template <typename T> T *GetSelf(lua_State *L) {
  return *(T **)lua_touserdata(L, 1);
}

template <typename T>
void VectorToTable(lua_State *L, const std::vector<T *> &items) {
  lua_newtable(L);
  for (size_t i = 0; i < items.size(); i++) {
    lua_pushinteger(L, i + 1);
    T::Lua(L, items[i]);
    lua_settable(L, -3);
  }
}