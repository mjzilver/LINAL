#include "Vector.h"
#include <cmath>
#include <iostream>

void Vector::print()
{
	std::cout << "Point: " << _x << ", " << _y << ", " << _z << std::endl;
}

Vector Vector::operator-(const Vector& other)
{
	return Vector(this->_x - other.getX(), this->_y - other.getY(), this->_z - other.getZ());
}

Vector Vector::operator+(const Vector& other)
{
	return Vector(this->_x + other.getX(), this->_y + other.getY(), this->_z+ other.getZ());
}

// cross product
Vector Vector::operator*(const Vector& other)
{
	return Vector(this->_y * other.getZ() - this->_z * other.getY(),
		this->_z * other.getX() - this->_x * other.getZ(),
		this->_x * other.getY() - this->_y * other.getX());
}

Vector Vector::operator*(const int value)
{
	Vector result;
	result.setX(this->_x * value);
	result.setY(this->_y * value);
	result.setZ(this->_z * value);

	return result;
}

float Vector::dotProduct(const Vector& other)
{
	return (getX() * other.getX()) + (getY() * other.getY() + (getZ() * other.getZ()));
}


void Vector::normalize()
{
	float length = std::sqrt(_x * _x + _y * _y + _z * _z);
	_x = _x / length;
	_y = _y / length;
	_z = _z / length;
}
