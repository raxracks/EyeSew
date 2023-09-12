#include "Color3.hpp"

Color3::Color3()
{
    R = 0;
    G = 0;
    B = 0;
    A = 1.0f;
}

Color3::Color3(float red, float green, float blue)
{
    R = red;
    G = green;
    B = blue;
    A = 1.0f;
}

Color3::Color3(float red, float green, float blue, float alpha)
{
    R = red;
    G = green;
    B = blue;
    A = alpha;
}
