#pragma once

class Point
{
public:
	Point(const double x, const double y, const double z) : _x{ x }, _y{ y }, _z{ z }, _w{1} {};
	Point() {};
	~Point(){};
	double getX() const { return _x; }
	double getY() const { return _y; }
	double getZ() const { return _z; }
	double getW() const { return _w; }

	void setX(const double x) { _x = x; }
	void setY(const double y) { _y = y; }
	void setZ(const double z) { _z = z; }
	void setW(const double w) { _w = w; }

	bool draw() { return _w >= 0; }

	void print();

	void normalize();
private:
	double _x;
	double _y;
	double _z;
	double _w;
};

