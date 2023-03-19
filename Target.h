#pragma once
#include "Vector.h"
#include "WorldObject.h"
#include "Matrix.h"

class Target :
	public WorldObject
{
public:
	Target(Vector start);
	~Target();

	void update();

	double scale = 1;
	int ticks = 0;
	bool increasing = true;
	Matrix position = Matrix(4, 4);
};

