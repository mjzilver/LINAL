#pragma once
#include "Point.h"
#include "WorldObject.h"

class Planet :
	public WorldObject
{
public:
	Planet(Point start);
	~Planet();
};

