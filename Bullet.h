#pragma once
#include "WorldObject.h"
class Bullet :
    public WorldObject
{
public:
    float speed{ 0.5f };
    Point force;
    Bullet(Point source, Point force, float speed);

    void update();
};

