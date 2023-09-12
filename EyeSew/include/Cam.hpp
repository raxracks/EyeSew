#pragma once
#include "Properties.hpp"
#include "Vec3.hpp"
#include <raylib.h>

class Cam {
public:
    Cam(Vec3& position, float& distance)
        : Position(position)
        , Distance(distance)
    {
    }

    Vec3& Position;
    float& Distance;

    operator Camera()
    {
        Camera camera {};
        camera.target = Position;
        camera.position = Vec3(Position.X + Distance, Position.Y + Distance, Position.Z + Distance);
        /*camera.target = Vec3(-Position.Y + (Position.X - (Position.X / 2)), 0, -Position.Y - (Position.X - (Position.X / 2)));
        camera.position = Vec3((-Position.Y + (Position.X - (Position.X / 2))) + Distance, Distance, (-Position.Y - (Position.X - (Position.X / 2))) + Distance);*/
        camera.fovy = Distance;
        camera.projection = CAMERA_ORTHOGRAPHIC;
        camera.up = Vec3(0, 1, 0);
        return camera;
    }

private:
};
