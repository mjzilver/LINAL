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
	position = Matrix(*this);
}

void Bullet::update()
{
	position = position.translate(
		force.getX() * speed,
		force.getY() * speed,
		force.getZ() * speed
	) * position;

	for (int i = 0; i < position.get_columns(); i++)
	{
		_points.at(i).setX(position.getValue(0, i));
		_points.at(i).setY(position.getValue(1, i));
		_points.at(i).setZ(position.getValue(2, i));
	}
}

