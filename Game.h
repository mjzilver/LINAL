#pragma once
#include "Render.h"
#include "Input.h"

class Game
{
public:
	Game();
	~Game();
	void StartGameLoop();
	void yaw();
	void pitch();
	void roll();
private:
	bool gameLoop = true;
	Render render{};
	Input input{};
};

