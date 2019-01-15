#pragma once
#include <vector>
#include <map>
#include "Point.h"

class WorldObject
{
public:
	WorldObject();
	~WorldObject();
	std::vector<Point>* get_object() { return &_points; }
	std::map<int,std::vector<Point*>> get_connections() { return _connections; }
	Point get_source() { return _source; }
protected:
	std::map<int, std::vector<Point*>> _connections;
	std::vector<Point> _points;
	Point _source;
};

