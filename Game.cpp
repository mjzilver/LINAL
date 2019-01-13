#include "Game.h"
#include "Render.h"
#include <iostream>

#include <SDL.h>
#include "Matrices.h"
#include "SpaceShip.h"
#undef main

Game::Game()
{
}


Game::~Game()
{
}

void Game::StartGameLoop()
{
	SDL_Event SDL_event;
	Point startLocation{ 400,400,10 };
	SpaceShip ship{ startLocation };

	while (gameLoop)
	{
		// input gedeelte
		input.resetKeys();

		if (SDL_PollEvent(&SDL_event)) {
			if (SDL_event.type == SDL_KEYDOWN)
			{
				input.keyDownEvent(SDL_event);
			}
			else if (SDL_event.type == SDL_KEYUP)
			{
				input.keyUpEvent(SDL_event);
			}
			else if (SDL_event.type == SDL_QUIT) {
				gameLoop = false;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			gameLoop = false;
		}


		

		render.Clear();

		render.DrawLine(10, 20, 40, 80,0,0,0);
		render.DrawObject(&ship);

		render.Draw();
	}
}
