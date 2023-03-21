#include "SpaceShip.h"
#include <iostream>

SpaceShip::SpaceShip(Vector source)
{
	_source = source;
	_points.push_back(_source);
	Vector point1{_source.getX()-25,_source.getY()-25,_source.getZ()};
	Vector point2{ _source.getX() - 25,_source.getY() - 25,_source.getZ() -50 };
	Vector point3{ _source.getX() - 25,_source.getY() + 25,_source.getZ() };
	Vector point4{ _source.getX() - 25,_source.getY() + 25,_source.getZ() -50};
	Vector point5{ _source.getX() + 25,_source.getY() - 25,_source.getZ() };
	Vector point6{ _source.getX() + 25,_source.getY() - 25,_source.getZ() -50};
	Vector point7{ _source.getX() + 25,_source.getY() + 25,_source.getZ() };
	Vector point8{ _source.getX() + 25,_source.getY() + 25,_source.getZ() -50};
	Vector point9{_source.getX() + 50, _source.getY(), _source.getZ()};
	Vector point10{ _source.getX() + 50, _source.getY(), _source.getZ()-50 };

	_points.push_back(point1);
	_points.push_back(point2);
	_points.push_back(point3);
	_points.push_back(point4);
	_points.push_back(point5);
	_points.push_back(point6);
	_points.push_back(point7);
	_points.push_back(point8);
	_points.push_back(point9);
	_points.push_back(point10);

	_connections[1].push_back(&_points[2]);
	_connections[1].push_back(&_points[3]);
	_connections[1].push_back(&_points[5]);
	_connections[4].push_back(&_points[2]);
	_connections[4].push_back(&_points[3]);
	_connections[4].push_back(&_points[8]);
	_connections[6].push_back(&_points[2]);
	_connections[6].push_back(&_points[5]);
	_connections[7].push_back(&_points[3]);
	_connections[7].push_back(&_points[8]);
	_connections[9].push_back(&_points[5]);
	_connections[9].push_back(&_points[7]);
	_connections[9].push_back(&_points[10]);
	_connections[10].push_back(&_points[6]);
	_connections[10].push_back(&_points[8]);

	position = Matrix(*this);
}


void SpaceShip::update()
{
	position = position.translate(
		force.getX() * speed,
		force.getY() * speed,
		force.getZ() * speed) * position;

	if (speed > 0.00f)
		speed -= 0.001f;
	else if (speed < 0.0f)
		speed = 0.0f;

	for (int i = 0; i < position.get_columns(); i++)
	{
		_points.at(i).setX(position.getValue(0, i));
		_points.at(i).setY(position.getValue(1, i));
		_points.at(i).setZ(position.getValue(2, i));
	}
}

void SpaceShip::rotate(Matrix rotation)
{
	Vector shipcenter = get_center();
	Matrix relative = position.getRelative(shipcenter);
	force = rotation.multiplyVector(force);
	relative = rotation * relative;
	position = relative.getAbsolute(shipcenter);
}

void SpaceShip::speedUp()
{
	if (speed < 0.5)
		speed += 0.005f;
}
