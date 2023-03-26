#pragma once
#include "WorldObject.h"
#include "Matrix.h"

class Bullet :
    public WorldObject
{
public:
    Bullet(Vector source, Vector force, float speed);

    float speed = 1.5f;
    Vector force;
    Matrix position;

    void update();
};

