#include "Camera.h"

Camera::Camera()
{
	this->eye = Vector{ 400, 400, 400 };
	this->lookat = Vector{ 400, 400, -1 };

	direction = eye - lookat;
	right = up * direction;
	up = direction * right;
}

void Camera::changePov(int change)
{
	if (currentPov + change > 0 && currentPov + change <= 5) {
		currentPov += change;
		if (currentPov == 1) {
			this->eye = Vector{ 400, 400, 400 };
			this->lookat = Vector{ 400, 400, -1 };
		}
		else if (currentPov == 2) {
			this->eye = Vector{ 800, 400, 100 };
			this->lookat = Vector{ 400, 400, -1 };
		}
		else if (currentPov == 3) {
			this->eye = Vector{ 400, 800, 100 };
			this->lookat = Vector{ 400, 400, -1 };
		} 
		else if (currentPov == 4) {
			this->eye = Vector{ 0, 800, 100 };
			this->lookat = Vector{ 400, 400, -1 };
		}
		else if (currentPov == 5) {
			this->eye = Vector{ 400, 400, -400 };
			this->lookat = Vector{ 400, 400, -1 };
		}
	}
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

	trans.setValues(std::vector<float>{
		right.getX(), right.getY(), right.getZ(), 0,
		up.getX(), up.getY(), up.getZ(), 0,
		direction.getX(), direction.getY(), direction.getZ(), 0,
		0, 0, 0, 1
	});

	local.setValues(std::vector<float>{
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
	float scale = _near * std::tan(fov * 0.5f);
	float a = -_far / (_far - _near);
	float b = (-_far * _near) / (_far - _near);

	Matrix projection{ 4,4 };
	projection.setValues(std::vector<float>{
		scale, 0, 0, 0,
			0, scale, 0, 0, 
			0, 0, a, -1, 
			0, 0, b, 0
	});

	return projection;
}