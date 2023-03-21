#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <cmath>

class Camera
{
public:
	Camera();

	Vector eye;
	Vector lookat;

	Vector direction;
	Vector up = Vector{0, 1, 0};
	Vector right;

	float fov = 80;
	float _far = 500;
	float _near = 50;

	int currentPov =1;

	Matrix getViewMatrix();
	Matrix getProjectionMatrix();
	void changePov(int change);
};

