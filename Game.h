#pragma once
#include "Render.h"
#include "Input.h"
#include "Camera.h"
#include "Vector.h"


class Game
{
public:
	Game();
	~Game();
	void StartGameLoop();
	bool BoxBoxCollision(BoundingBox a, BoundingBox b);
private:
	bool gameLoop = true;
	Render render;
	Input input;
	Camera camera = Camera(Vector{ 100, 0, 100 },
		Vector{ -100, -50, -1 });
};

