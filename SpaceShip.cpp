#include "SpaceShip.h"

SpaceShip::SpaceShip(Point source)
{
	_source = source;
	_points.push_back(_source);
	Point point1{_source.getX()-25,_source.getY()-25,_source.getZ()};
	Point point2{ _source.getX() - 25,_source.getY() - 25,_source.getZ() -50 };
	Point point3{ _source.getX() - 25,_source.getY() + 25,_source.getZ() };
	Point point4{ _source.getX() - 25,_source.getY() + 25,_source.getZ() -50};
	Point point5{ _source.getX() + 25,_source.getY() - 25,_source.getZ() };
	Point point6{ _source.getX() + 25,_source.getY() - 25,_source.getZ() -50};
	Point point7{ _source.getX() + 25,_source.getY() + 25,_source.getZ() };
	Point point8{ _source.getX() + 25,_source.getY() + 25,_source.getZ() -50};

	_points.push_back(point1);
	_points.push_back(point2);
	_points.push_back(point3);
	_points.push_back(point4);
	_points.push_back(point5);
	_points.push_back(point6);
	_points.push_back(point7);
	_points.push_back(point8);

	_connections[1].push_back(&_points[2]);
	_connections[1].push_back(&_points[3]);
	_connections[1].push_back(&_points[5]);
	_connections[4].push_back(&_points[2]);
	_connections[4].push_back(&_points[3]);
	_connections[4].push_back(&_points[8]);
	_connections[6].push_back(&_points[2]);
	_connections[6].push_back(&_points[5]);
	_connections[6].push_back(&_points[8]);
	_connections[7].push_back(&_points[3]);
	_connections[7].push_back(&_points[5]);
	_connections[7].push_back(&_points[8]);
}

SpaceShip::~SpaceShip()
{
}
