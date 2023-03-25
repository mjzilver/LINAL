#pragma once
#include "WorldObject.h"
#include "Matrix.h"
#include "Camera.h"

class SpaceShip :
	public WorldObject
{
public:
	SpaceShip(Vector source);

	float speed = 0.0f;
	Vector movement = Vector(_source);
	Vector force = Vector(1, 0, 0);
	Matrix position;

	void update();
	void rotate(Matrix rotmat);
	void speedUp();
};

