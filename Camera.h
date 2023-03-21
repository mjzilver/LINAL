#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <cmath>

class Camera
{
public:
	Camera(Vector position, Vector lookat);

	Vector eye;
	Vector lookat;

	Vector direction;
	Vector up = Vector{0, 1, 0};
	Vector right;

	int fov = 80;
	int _far = 100;
	int _near = 1;

	Matrix getViewMatrix();
	Matrix getProjectionMatrix();

};

