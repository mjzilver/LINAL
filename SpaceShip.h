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
	Point force = Point(1, 0, 0);
	Matrix position = Matrix(4, 4);

	void update();
	void rotate(Matrix rotmat);
	void speedUp();

	~SpaceShip();
};

