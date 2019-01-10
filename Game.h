#pragma once
#include "Render.h"
#include "Input.h"

class Game
{
public:
	Game();
	~Game();
	void StartGameLoop();
private:
	bool gameLoop = true;
	Render render{};
	Input input{};
};

