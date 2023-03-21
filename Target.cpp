#include "Target.h"
#include "Vector.h"

Target::Target(Vector start)
{
	_source = start;
	_points.push_back(_source);
	Vector point1{ _source.getX() - 30,_source.getY() - 30,_source.getZ() };
	Vector point2{ _source.getX() - 30,_source.getY() - 30,_source.getZ() - 30 };
	Vector point3{ _source.getX() - 30,_source.getY() + 30,_source.getZ() };
	Vector point4{ _source.getX() - 30,_source.getY() + 30,_source.getZ() - 30 };
	Vector point5{ _source.getX() + 30,_source.getY() - 30,_source.getZ() };
	Vector point6{ _source.getX() + 30,_source.getY() - 30,_source.getZ() - 30 };
	Vector point7{ _source.getX() + 30,_source.getY() + 30,_source.getZ() };
	Vector point8{ _source.getX() + 30,_source.getY() + 30,_source.getZ() - 30 };

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
	position = Matrix(*this);
}

void Target::update()
{
	ticks++;

	if (increasing)
		scale += 0.000001;
	else
		scale -= 0.000001;

	if (scale >= 1.0005)
		increasing = false;
	else if (scale < 0.9995)
		increasing = true;

	position = position.scale(*this, scale, scale, scale);
	for (int i = 0; i < position.get_columns(); i++)
	{
		_points.at(i).setX(position.getValue(0, i));
		_points.at(i).setY(position.getValue(1, i));
		_points.at(i).setZ(position.getValue(2, i));
	}
}
