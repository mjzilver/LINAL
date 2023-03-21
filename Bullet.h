#pragma once
#include "WorldObject.h"
#include "Matrix.h"
class Bullet :
    public WorldObject
{
public:
    Bullet(Vector source, Vector force, float speed);

    float speed{ 0.5f };
    Vector force;
    Matrix position = Matrix();

    void update();
};

