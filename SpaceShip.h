#pragma once
#include "WorldObject.h"
#include "Vector3d.h"
#include "Matrix.h"

class SpaceShip :
	public WorldObject
{
public:
	SpaceShip(Point source);

	float speed{ 0.0f };
	vector3d movement = vector3d(_source, _source);
	Point force = Point(0.1f, 0.0f, 0);
	Matrix position = Matrix(*this);

	void give_gas();
	void update();

	void pitch(double degrees);
	void yaw(double degrees);
	void roll(double degrees);


	~SpaceShip();
};

