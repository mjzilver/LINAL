#pragma once
#include "WorldObject.h"
#include "Matrix.h"
class Bullet :
    public WorldObject
{
public:
    Bullet(Point source, Point force, float speed);

    float speed{ 0.5f };
    Point force;
    Matrix position = Matrix(4, 4);

    void update();
};

