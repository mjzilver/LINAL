#pragma once
class Point
{
public:
	Point(const int x, const int y, const int z) : _x{ x }, _y{ y }, _z{ z }, _worldX{ x }, _worldY{ y }, _w{1} {};
	Point() {};
	~Point(){};
	int getX() const { return _x; }
	int getY() const { return _y; }
	int getZ() const { return _z; }
	void setX(const int x) { _x = x; }
	void setY(const int y) { _y = y; }
	void setZ(const int z) { _z = z; }

	int getWorldX() const { return _worldX; }
	int getWorldY() const { return _worldY; }
	void setWorldX(const int x) { _worldX = x; }
	void setWorldY(const int y) { _worldY = y; }
	void setW(const int w) { _w = w; }
	bool draw() { return _w >= 0; }
private:
	int _x;
	int _y;
	int _z;
	int _worldX;
	int _worldY;
	int _w;
};

