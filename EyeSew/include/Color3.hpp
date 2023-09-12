#pragma once
#include <cstdint>
#include <raylib.h>

class Color3 {
public:
    Color3();
    Color3(float red, float green, float blue);
    Color3(float red, float green, float blue, float alpha);

    operator Color()
    {
        return Color { static_cast<uint8_t>(R * 255.0f), static_cast<uint8_t>(G * 255.0f), static_cast<uint8_t>(B * 255.0f), static_cast<uint8_t>(A * 255.0f) };
    }

    float R;
    float G;
    float B;
    float A;
};
