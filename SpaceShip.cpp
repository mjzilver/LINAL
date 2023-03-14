#include "SpaceShip.h"
#include <iostream>

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
	Point point9{_source.getX() + 50, _source.getY(), _source.getZ()};
	Point point10{ _source.getX() + 50, _source.getY(), _source.getZ()-50 };

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
}

void SpaceShip::give_gas()
{
	if (speed < 10)
		speed += 0.1f;
}

void SpaceShip::update() 
{
	position = position.translate(force.getX() * speed, force.getY() * speed, force.getZ() * speed) * position;

	if (speed > 0.00f)
		speed -= 0.05f;
	else if (speed < 0.0f)
		speed = 0.0f;
}

void SpaceShip::pitch(double degrees)
{
	std::cout << "Now printing start matrix" << std::endl;
	position.print();
	std::cout << "Now printing trans matrix" << std::endl;
	position = position.pitch(degrees) * position;
	position.pitch(degrees).print();
	std::cout << "Now printing result matrix" << std::endl;
	position.print();
}

void SpaceShip::yaw(double degrees)
{
}

void SpaceShip::roll(double degrees)
{

}

SpaceShip::~SpaceShip()
{
}
