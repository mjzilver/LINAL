#pragma once
class Point
{
public:
	Point(const double x, const double y, const double z) : _x{ x }, _y{ y }, _z{ z }, _worldX{ x }, _worldY{ y }, _w{1} {};
	Point() {};
	~Point(){};
	double getX() const { return _x; }
	double getY() const { return _y; }
	double getZ() const { return _z; }
	void setX(const double x) { _x = x; }
	void setY(const double y) { _y = y; }
	void setZ(const double z) { _z = z; }

	int getWorldX() const { return _worldX; }
	int getWorldY() const { return _worldY; }
	void setWorldX(const double x) { _worldX = x; }
	void setWorldY(const double y) { _worldY = y; }
	void setW(const int w) { _w = w; }
	bool draw() { return _w >= 0; }
private:
	double _x;
	double _y;
	double _z;
	double _worldX;
	double _worldY;
	int _w;
};

