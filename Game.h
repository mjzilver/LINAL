#pragma once
#include "Render.h"
#include "Input.h"

class Game
{
public:
	Game();
	~Game();
	void StartGameLoop();
	bool BoxBoxCollision(BoundingBox a, BoundingBox b);
private:
	bool gameLoop = true;
	Render render{};
	Input input{};
};

