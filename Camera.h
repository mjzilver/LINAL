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

	Matrix getViewMatrix();
	Matrix getProjectionMatrix();
	// cycle through various points of view
	void changePov(int change);
private:
	float fov = 80;
	float _far = 500;
	float _near = 50;
	int currentPov = 1;

};

