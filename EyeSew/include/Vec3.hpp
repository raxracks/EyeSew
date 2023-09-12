#pragma once
#include <raylib.h>

class Vec3 {
public:
    Vec3();
    Vec3(float X, float Y, float Z);

    operator Vector3()
    {
        return Vector3 { X, Y, Z };
    }

    float X;
    float Y;
    float Z;
};
