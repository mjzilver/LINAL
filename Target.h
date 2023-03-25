#pragma once
#include "Vector.h"
#include "WorldObject.h"
#include "Matrix.h"

class Target :
	public WorldObject
{
public:
	Target(Vector start);

	void update();
	Matrix position;
private:
	float scale = 1;
	int ticks = 0;
	bool increasing = true;
};

