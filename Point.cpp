#include "Point.h"
#include <cmath>
#include <iostream>

void Point::print()
{
	std::cout << "Point: " << _x << ", " << _y << ", " << _z << std::endl;
}

void Point::normalize()
{
	double length = std::sqrt(_x * _x + _y * _y + _z * _z);
	_x = _x / length;
	_y = _y / length;
	_z = _z / length;
}
