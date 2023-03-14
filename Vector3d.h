#pragma once

#include "Point.h"

class vector3d
{
public:
	vector3d(const Point a, const Point b) : _point_a(a), _point_b(b) {};

	Point getA() const { return _point_a; }
	Point getB() const { return _point_b; }

	void setA(const Point a) { _point_a = a; }
	void setB(const Point b) { _point_b = b; }


private:
	Point _point_a;
	Point _point_b;
};

