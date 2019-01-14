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
	SpaceShip ship { startLocation };
	SpaceShip ship2{ startLocation };
	SpaceShip ship3{ startLocation };
	bool scaled = false;

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
		render.DrawObject(&ship2);
		render.DrawObject(&ship3);

		render.Draw();
		Matrix shipPosition{ ship };
		Matrix shipPosition2{ ship2 };

		if(!scaled)
		{
			//shipPosition = shipPosition.scale(ship, 2, 2, 1);
			shipPosition = shipPosition.rotate(ship, ship.get_source(), 10);
			for (int i = 0; i < shipPosition.get_columns(); i++)
			{
				ship.get_object()->at(i).setX(shipPosition.getValue(0, i));
				ship.get_object()->at(i).setY(shipPosition.getValue(1, i));
				ship.get_object()->at(i).setZ(shipPosition.getValue(2, i));
			}
			shipPosition2 = shipPosition2.rotate(ship2, ship2.get_source(), 90);
			for (int i = 0; i < shipPosition.get_columns(); i++)
			{
				ship2.get_object()->at(i).setX(shipPosition2.getValue(0, i));
				ship2.get_object()->at(i).setY(shipPosition2.getValue(1, i));
				ship2.get_object()->at(i).setZ(shipPosition2.getValue(2, i));
			}
			scaled = true;
		}

		/*shipPosition = shipPosition.translate(ship, 1, 1, 0);
		for (int i = 0; i < shipPosition.get_columns(); i++)
		{
			ship.get_object()->at(i).setX(shipPosition.getValue(0, i));
			ship.get_object()->at(i).setY(shipPosition.getValue(1, i));
			ship.get_object()->at(i).setZ(shipPosition.getValue(2, i));
		}*/
	}
}
