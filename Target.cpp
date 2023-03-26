#include "Target.h"

Target::Target(Vector start)
{
	_source = start;
	_coords = _source;
	Vector point1{ -30,-30,0 };
	Vector point2{ -30,-30,-30 };
	Vector point3{ -30,30,0 };
	Vector point4{ -30,30,-30 };
	Vector point5{ 30,-30,0 };
	Vector point6{ 30,-30,- 30 };
	Vector point7{ 30,30,0 };
	Vector point8{ 30,30,-30 };

	_points.push_back(point1);
	_points.push_back(point2);
	_points.push_back(point3);
	_points.push_back(point4);
	_points.push_back(point5);
	_points.push_back(point6);
	_points.push_back(point7);
	_points.push_back(point8);

	_connections[0].push_back(&_points[1]);
	_connections[0].push_back(&_points[2]);
	_connections[0].push_back(&_points[4]);
	_connections[3].push_back(&_points[1]);
	_connections[3].push_back(&_points[2]);
	_connections[3].push_back(&_points[7]);
	_connections[5].push_back(&_points[1]);
	_connections[5].push_back(&_points[4]);
	_connections[5].push_back(&_points[7]);
	_connections[6].push_back(&_points[2]);
	_connections[6].push_back(&_points[4]);
	_connections[6].push_back(&_points[7]);
	position = Matrix(*this);
	name = "target";
}

void Target::update()
{
	ticks++;

	if (increasing)
		scale += 0.000001f;
	else
		scale -= 0.000001f;

	if (scale >= 1.0005)
		increasing = false;
	else if (scale < 0.9995)
		increasing = true;

	position = position.scale(*this, scale, scale, scale) * position;
	for (int i = 0; i < position.get_columns(); i++)
	{
		_points.at(i).setX(position.getValue(0, i));
		_points.at(i).setY(position.getValue(1, i));
		_points.at(i).setZ(position.getValue(2, i));
	}
}
