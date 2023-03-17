#pragma once
#include "WorldObject.h"
#include "Matrix.h"

class SpaceShip :
	public WorldObject
{
public:
	SpaceShip(Point source);

	float speed{ 0.0f };
	Point movement = Point(_source);
	Point force = Point(0.1f, 0, 0);
	Matrix position = Matrix(*this);

	~SpaceShip();
};

