#pragma once

class Vector
{
public:
	Vector(const double x, const double y, const double z) : _x{ x }, _y{ y }, _z{ z }, _w{1} {};
	Vector() : _x{ 0 }, _y{ 0 }, _z{ 0 }, _w{ 1 } {};
	~Vector(){};
	double getX() const { return _x; }
	double getY() const { return _y; }
	double getZ() const { return _z; }
	double getW() const { return _w; }

	void setX(const double x) { _x = x; }
	void setY(const double y) { _y = y; }
	void setZ(const double z) { _z = z; }
	void setW(const double w) { _w = w; }

	void print();

	Vector operator-(const Vector& other);
	Vector operator+(const Vector& other);
	Vector operator*(const Vector& other);

	void normalize();
private:
	double _x;
	double _y;
	double _z;
	double _w;
};

