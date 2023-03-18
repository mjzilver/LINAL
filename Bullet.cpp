#include "Bullet.h"

Bullet::Bullet(Point source, Point force, float speed)
{
	this->speed += speed;
	_source = source;
	this->force = force;
	_points.push_back(_source);
	Point point1{source.getX() + force.getX() * 10,
		source.getY() + force.getY() * 10,
		source.getZ() + force.getZ() * 10};
	_points.push_back(point1);

	_connections[0].push_back(&_points[1]);
}

void Bullet::update()
{
	_points[0].setX(_points[0].getX() + (force.getX() * speed));
	_points[0].setY(_points[0].getY() + (force.getY() * speed));
	_points[0].setZ(_points[0].getZ() + (force.getZ() * speed));

	_points[1].setX(_points[1].getX() + (force.getX() * speed));
	_points[1].setY(_points[1].getY() + (force.getY() * speed));
	_points[1].setZ(_points[1].getZ() + (force.getZ() * speed));
}

