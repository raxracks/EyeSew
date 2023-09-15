#include "Instance.hpp"

Instance::Instance(const std::string className)
    : Camera(Cam(Position, Distance)), ClassName(className), Name(className),
      Properties(CalculateProperties()) {}

Instance::Instance(const std::string className, Instance *parent)
    : Camera(Cam(Position, Distance)), ClassName(className), Name(className),
      Properties(CalculateProperties()) {
  SetParent(parent);
}

void Instance::SetParent(Instance *parent) {
  if (Parent != nullptr) {
    if (next != nullptr) {
      next->prev = prev;
    }
    if (prev != nullptr) {
      prev->next = next;
    }

    if (Parent->child == this) {
      Parent->child = next;
    }
  }
  Parent = parent;
  Instance *current = Parent->child;
  next = nullptr;
  if (current == nullptr) {
    Parent->child = this;
    prev = nullptr;
  } else {
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = this;
    prev = current;
  }
}

const std::vector<Instance *> &Instance::GetChildren() {
  children.clear();
  Instance *current = child;
  while (current != nullptr) {
    children.push_back(current);
    current = current->next;
  }

  return children;
}

const std::vector<Instance *> &Instance::GetDescendants() {
  descendants.clear();
  AddDescendants(this);
  return descendants;
}

Instance *Instance::FindFirstChild(const std::string name) {
  const std::vector<Instance *> &children = GetChildren();

  auto it = std::ranges::find_if(
      children, [&](Instance *child) { return child->Name == name; });

  if (it != children.end())
    return *it;
  else
    return nullptr;
}

void Instance::Destroy() {
  destroyed = true;

  Instance *c = child;
  while (c != nullptr) {
    c->Destroy();
    c = c->next;
  }
}

bool Instance::IsA(const std::string className) {
  return ClassName == className;
}

void Instance::AddDescendants(Instance *root) {
  for (Instance *child : root->GetChildren()) {
    descendants.push_back(child);
    AddDescendants(child);
  }
}

const uint32_t Instance::CalculateProperties() {
  if (IsA("Part")) {
    return Properties::Position | Properties::Size | Properties::Color;
  } else if (IsA("Script")) {
    return Properties::Code;
  } else if (IsA("Camera")) {
    return Properties::Position | Properties::Distance;
  }

  return 0;
}

void Instance::Metatable(lua_State *L) {
  luaL_newmetatable(L, "Instance");
  lua_pushstring(L, "__index");
  pushfunction(L, Instance::__index);
  lua_settable(L, -3);
  lua_pushstring(L, "__newindex");
  pushfunction(L, Instance::__newindex);
  lua_settable(L, -3);
}

void Instance::Lua(lua_State *L, Instance *instance) {
  Instance **pInstance = (Instance **)lua_newuserdata(L, sizeof(Instance *));
  *pInstance = instance;

  luaL_getmetatable(L, "Instance");
  lua_setmetatable(L, -2);
}

int Instance::__index(lua_State *L) {
  Instance *self = *(Instance **)lua_touserdata(L, 1);
  std::string key = lua_tostring(L, 2);
  if (key == "Name")
    lua_pushstring(L, self->Name.c_str());
  else if (key == "Parent")
    Instance::Lua(L, self->Parent);
  else if (key == "GetChildren")
    pushfunction(L, [](lua_State *L) {
      VectorToTable<Instance>(L, GetSelf<Instance>(L)->GetChildren());

      return 1;
    });
  else if (key == "GetDescendants")
    pushfunction(L, [](lua_State *L) {
      VectorToTable<Instance>(L, GetSelf<Instance>(L)->GetChildren());

      return 1;
    });
  else if (key == "IsA")
    pushfunction(L, [](lua_State *L) {
      lua_pushboolean(L, GetSelf<Instance>(L)->IsA(lua_tostring(L, 2)));

      return 1;
    });
  else if (key == "FindFirstChild")
    pushfunction(L, [](lua_State *L) {
      Instance *child =
          GetSelf<Instance>(L)->FindFirstChild(lua_tostring(L, 2));

      if (child != nullptr)
        Instance::Lua(L, child);
      else
        lua_pushnil(L);

      return 1;
    });
  else if (key == "Position")
    Vec3::Lua(L, &self->Position);
  else if (key == "Color")
    Color3::Lua(L, &self->Color);
  else
    Instance::Lua(L, self->FindFirstChild(key));

  return 1;
}

int Instance::__newindex(lua_State *L) {
  Instance *self = *(Instance **)lua_touserdata(L, 1);
  std::string key = lua_tostring(L, 2);
  if (key == "Name")
    self->Name = lua_tostring(L, 3);
  else if (key == "Parent")
    self->SetParent(*(Instance **)lua_touserdata(L, 3));
  else if (key == "Color")
    self->Color = **(Color3 **)lua_touserdata(L, 3);
  else if (key == "Position")
    self->Position = **(Vec3 **)lua_touserdata(L, 3);

  return 0;
}