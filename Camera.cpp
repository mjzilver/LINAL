#include "Camera.h"
#include <iostream>

Camera::Camera(Vector eye, Vector lookat)
{
	this->eye = eye;
	this->lookat = lookat;

	direction = eye - lookat;
	right = up * direction;
	up = direction * right;
}

Matrix Camera::getViewMatrix()
{
	direction = eye - lookat;
	right = up * direction;
	up = direction * right;

	Matrix trans{ 4,4 };
	Matrix local{ 4,4 };

	right.normalize();
	up.normalize();
	direction.normalize();

	trans.setValues(std::vector<double>{
		right.getX(), right.getY(), right.getZ(), 0,
		up.getX(), up.getY(), up.getZ(), 0,
		direction.getX(), direction.getY(), direction.getZ(), 0,
		0, 0, 0, 1
	});

	local.setValues(std::vector<double>{
		1, 0, 0, -eye.getX(),
			0, 1, 0, -eye.getY(),
			0, 0, 1, -eye.getZ(),
			0, 0, 0, 1
	});
	trans = trans * local;

	return trans;
}

Matrix Camera::getProjectionMatrix()
{
	float scale = _near * std::tan(fov * 0.5);
	float a = -_far / (_far - _near);
	float b = (-_far * _near) / (_far - _near);

	Matrix projection{ 4,4 };
	projection.setValues(std::vector<double>{
		scale, 0, 0, 0,
			0, scale, 0, 0, 
			0, 0, a, -1, 
			0, 0, b, 0
	});

	a = -((_far + _near) / (_far - _near));
	b = -(2 * (_near * _far) / (_far - _near));

	Matrix projection2{ 4,4 };

	projection2.setValues(std::vector<double>{
		std::atan(fov/2), 0, 0, 0,
			0, std::atan(fov/2), 0, 0,
			0, 0, a, b,
			0, 0, -1, 0
	});

	return projection;
}