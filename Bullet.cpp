#include "Bullet.h"

Bullet::Bullet(Vector source, Vector force, float speed)
{
	this->speed += speed;
	_source = source;
	this->force = force;
	_coords = source + force;

	//_points.push_back(_source);
	Vector point0 = force;
	Vector point1 = force * 10;
	_points.push_back(point0);
	_points.push_back(point1);

	_connections[0].push_back(&_points[1]);
	position = Matrix(*this);
	name = "bullet";
}

void Bullet::update()
{
	Matrix translationMatrix = Matrix::translate(force.getX() * speed,
		force.getY() * speed,
		force.getZ() * speed);

	_coords = translationMatrix.multiplyVector(_coords);
}

