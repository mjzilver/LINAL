#pragma once

class Vector
{
public:
	Vector(const float x, const float y, const float z) : _x{ x }, _y{ y }, _z{ z }, _w{1} {};
	Vector(const float x, const float y, const float z, const float w) : _x{ x }, _y{ y }, _z{ z }, _w{ w } {};
	Vector() : _x{ 0 }, _y{ 0 }, _z{ 0 }, _w{ 1 } {};
	~Vector(){};
	float getX() const { return _x; }
	float getY() const { return _y; }
	float getZ() const { return _z; }
	float getW() const { return _w; }

	void setX(const float x) { _x = x; }
	void setY(const float y) { _y = y; }
	void setZ(const float z) { _z = z; }
	void setW(const float w) { _w = w; }

	void print(); // debug function 

	Vector operator-(const Vector& other);
	Vector operator+(const Vector& other);
	Vector operator*(const Vector& other); // cross product
	Vector operator*(const int value); 

	float dotProduct(const Vector& other);

	void normalize();
private:
	float _x;
	float _y;
	float _z;
	float _w;
};

