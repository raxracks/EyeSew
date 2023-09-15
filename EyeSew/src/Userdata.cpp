#include "Userdata.hpp"

void Userdata::RegisterUserdata() {
  Instance::Metatable(m_State);

  const luaL_Reg instanceLibrary[] = {
      {
          "new",
          [](lua_State *L) {
            int argc = lua_gettop(L);
            if (argc == 1)
              Instance::Lua(L, new Instance(lua_tostring(L, 1)));
            else if (argc == 2)
              Instance::Lua(L,
                            new Instance(lua_tostring(L, 1),
                                         *((Instance **)lua_touserdata(L, 2))));
            else
              luaL_error(L, "Instance.new() called with invalid arguments!");
            return 1;
          },
      },
      {NULL, NULL}};

  luaL_register(m_State, "Instance", instanceLibrary);

  // m_State.new_usertype<Instance>(
  //     "Instance",
  //     sol::no_constructor,

  //     "new",
  //     sol::overload(
  //         [](std::string type)
  //         {
  //             return new Instance(type);
  //         },
  //         [](std::string type, Instance *parent)
  //         {
  //             return new Instance(type, parent);
  //         }),

  //     "Name",
  //     &Instance::Name,
  //     "ClassName",
  //     sol::readonly(&Instance::ClassName),
  //     "FindFirstChild",
  //     &Instance::FindFirstChild,
  //     "GetChildren",
  //     &Instance::GetChildren,
  //     "GetDescendants",
  //     &Instance::GetDescendants,
  //     /*"Clone",
  //     &Instance::Clone,*/
  //     "Destroy",
  //     &Instance::Destroy,
  //     "IsA",
  //     &Instance::IsA,

  //     "Position",
  //     &Instance::Position,
  //     "Size",
  //     &Instance::Size,
  //     "Color",
  //     &Instance::Color,
  //     "Distance",
  //     &Instance::Distance,

  //     sol::meta_function::index,
  //     &Instance::Index,
  //     sol::meta_function::new_index,
  //     &Instance::NewIndex);

  // m_State.new_usertype<Vec3>("Vector3",
  //                            sol::constructors<Vec3(), Vec3(float, float,
  //                            float)>(),

  //                            "X",
  //                            &Vec3::X,
  //                            "Y",
  //                            &Vec3::Y,
  //                            "Z",
  //                            &Vec3::Z);

  Vec3::Metatable(m_State);

  const luaL_Reg vec3Library[] = {
      {
          "new",
          [](lua_State *L) {
            int argc = lua_gettop(L);
            if (argc == 0)
              Vec3::Lua(L, new Vec3());
            else if (argc == 3)
              Vec3::Lua(L, new Vec3(lua_tonumber(L, 1), lua_tonumber(L, 2),
                                    lua_tonumber(L, 3)));
            else
              luaL_error(L, "Vector3.new() called with invalid arguments!");
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
            std::cout << "new color" << std::endl;
            int argc = lua_gettop(L);
            if (argc == 0)
              Color3::Lua(L, new Color3());
            else if (argc == 3)
              Color3::Lua(L, new Color3(lua_tonumber(L, 1), lua_tonumber(L, 2),
                                        lua_tonumber(L, 3)));
            else if (argc == 4)
              Color3::Lua(L,
                          new Color3(lua_tonumber(L, 1), lua_tonumber(L, 2),
                                     lua_tonumber(L, 3), lua_tonumber(L, 4)));
            else
              luaL_error(L, "Color3.new() called with invalid arguments!");
            return 1;
          },

      },
      {NULL, NULL}};

  luaL_register(m_State, "Color3", color3Library);
  // m_State.new_usertype<Color3>("Color3",
  //                              sol::constructors<Color3(),
  //                                                Color3(float, float, float),
  //                                                Color3(float, float, float,
  //                                                float)>(),

  //                              "R",
  //                              &Color3::R,
  //                              "G",
  //                              &Color3::G,
  //                              "B",
  //                              &Color3::B,
  //                              "A",
  //                              &Color3::A);
}
