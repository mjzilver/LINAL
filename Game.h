#pragma once
#include <windows.h>
#include <stdlib.h>
#include <algorithm>
#include <SDL.h>

#include "Render.h"
#include "Input.h"
#include "Camera.h"
#include "Vector.h"
#include "Matrix.h"
#include "SpaceShip.h"
#include "Target.h"
#include "Bullet.h"

class Game
{
public:
	void StartGameLoop();
	bool BoxBoxCollision(BoundingBox a, BoundingBox b);
private:
	bool gameLoop = true;
	Render render;
	Input input;
	Camera camera = Camera();
};

