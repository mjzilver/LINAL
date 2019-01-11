#pragma once
class Vector
{
public:
	Vector(int x, int y, int z) : _delta_X{ x }, _delta_Y{ y }, _delta_Z{ z }{}
	~Vector() {}
private:
	int _delta_X;
	int _delta_Y;
	int _delta_Z;
};

