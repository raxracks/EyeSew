#include "Userdata.hpp"

void Userdata::RegisterUserdata() {
  Instance::Metatable(m_State);

  const luaL_Reg instanceLibrary[] = {
      {"new",
       [](lua_State *L) {
         switch (lua_gettop(L)) {
         case 1:
           Instance::Lua(L, new Instance(lua_tostring(L, 1)));
           break;
         case 2:
           Instance::Lua(L, new Instance(lua_tostring(L, 1),
                                         *((Instance **)lua_touserdata(L, 2))));
           break;
         default:
           luaL_error(L, "Instance.new() called with invalid arguments!");
         }

         return 1;
       }},
      {NULL, NULL}};

  luaL_register(m_State, "Instance", instanceLibrary);

  Vec3::Metatable(m_State);

  const luaL_Reg vec3Library[] = {
      {
          "new",
          [](lua_State *L) {
            switch (lua_gettop(L)) {
            case 0:
              Vec3::Lua(L, new Vec3());
              break;
            case 3:
              Vec3::Lua(L, new Vec3(lua_tonumber(L, 1), lua_tonumber(L, 2),
                                    lua_tonumber(L, 3)));
              break;
            default:
              luaL_error(L, "Vector3.new() called with invalid arguments!");
            }

            return 1;
          },
      },
      {NULL, NULL}};

  luaL_register(m_State, "Vector3", vec3Library);

  Color3::Metatable(m_State);

  const luaL_Reg color3Library[] = {
      {
          "new",
          [](lua_State *L) {
            switch (lua_gettop(L)) {
            case 0:
              Color3::Lua(L, new Color3());
              break;
            case 3:
              Color3::Lua(L, new Color3(lua_tonumber(L, 1), lua_tonumber(L, 2),
                                        lua_tonumber(L, 3)));
              break;
            case 4:
              Color3::Lua(L,
                          new Color3(lua_tonumber(L, 1), lua_tonumber(L, 2),
                                     lua_tonumber(L, 3), lua_tonumber(L, 4)));
              break;
            default:
              luaL_error(L, "Color3.new() called with invalid arguments!");
            }

            return 1;
          },

      },
      {NULL, NULL}};

  luaL_register(m_State, "Color3", color3Library);
}
