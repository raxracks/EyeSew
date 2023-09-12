#include "Instance.hpp"
#include <iostream>

Instance::Instance(const std::string className)
    : Camera(Cam(Position, Distance))
    , ClassName(className)
    , Name(className)
    , Properties(CalculateProperties())
{
}

Instance::Instance(const std::string className, Instance* parent)
    : Camera(Cam(Position, Distance))
    , ClassName(className)
    , Name(className)
    , Properties(CalculateProperties())
{
    SetParent(parent);
}

void Instance::SetParent(Instance* parent)
{
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
    Instance* current = Parent->child;
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

const std::vector<Instance*>& Instance::GetChildren()
{
    children.clear();
    Instance* current = child;
    while (current != nullptr) {
        children.push_back(current);
        current = current->next;
    }

    return children;
}

const std::vector<Instance*>& Instance::GetDescendants()
{
    descendants.clear();
    AddDescendants(this);
    return descendants;
}

Instance* Instance::FindFirstChild(const std::string name)
{
    const std::vector<Instance*>& children = GetChildren();

    auto it = std::ranges::find_if(children, [&](Instance* child) {
        return child->Name == name;
    });

    if (it != children.end())
        return *it;
    else
        return nullptr;
}

void Instance::Destroy()
{
    destroyed = true;

    Instance* c = child;
    while (c != nullptr) {
        c->Destroy();
        c = c->next;
    }
}

bool Instance::IsA(const std::string className)
{
    return ClassName == className;
}

void Instance::AddDescendants(Instance* root)
{
    for (Instance* child : root->GetChildren()) {
        descendants.push_back(child);
        AddDescendants(child);
    }
}

Instance* Instance::Index(const std::string name)
{
    if (name == "Parent")
        return Parent;

    return FindFirstChild(name);
}

void Instance::NewIndex(std::string key, Instance* parent)
{
    if (key == "Parent")
        SetParent(parent);
}

const uint32_t Instance::CalculateProperties()
{
    if (IsA("Part")) {
        return Properties::Position | Properties::Size | Properties::Color;
    } else if (IsA("Script")) {
        return Properties::Code;
    } else if (IsA("Camera")) {
        return Properties::Position | Properties::Distance;
    }

    return 0;
}
