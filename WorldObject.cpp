#include "WorldObject.h"
#include <iostream>

WorldObject::WorldObject()
{
}

WorldObject::~WorldObject()
{
}

Point WorldObject::get_center()
{
	float x = 0;
	float y = 0;
	float z = 0;
	for (int i = 0; i < _points.size(); i++){
		x += _points[i].getX();
		y += _points[i].getY();
		z += _points[i].getZ();
	}

	x /= _points.size();
	y /= _points.size();
	z /= _points.size();

	return Point(x, y, z);
}
