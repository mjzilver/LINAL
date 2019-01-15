#include "Game.h"
#include "Render.h"
#include <iostream>

#include <SDL.h>
#include "Matrices.h"
#include "SpaceShip.h"
#include "Planet.h"
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
	Point planetLocation{ 800, 200, 300 };
	Planet planet{ planetLocation };
	double planetpulse = 1;
	int ticks = 0;
	bool planetincrease = true;

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

		render.DrawObject(&ship);
		render.DrawObject(&planet);
		render.DrawLine(0, 0, ship.get_object()->at(0).getX(), ship.get_object()->at(0).getY());
		render.Draw();
		Matrix shipPosition{ ship };
		Matrix planetPosition{ planet };

		ticks++;

		if(input.isKeyHeld(SDL_SCANCODE_LSHIFT))
		{
			shipPosition = shipPosition.translate(ship, 0.1, 0, 0);
		}

		if (input.isKeyHeld(SDL_SCANCODE_Q))
		{
			shipPosition = shipPosition.rotate(ship, ship.get_object()->at(0), 1);
			for (int i = 0; i < shipPosition.get_columns(); i++)
			{
				ship.get_object()->at(i).setX(shipPosition.getValue(0, i));
				ship.get_object()->at(i).setY(shipPosition.getValue(1, i));
				ship.get_object()->at(i).setZ(shipPosition.getValue(2, i));
			}
		}

		if (input.isKeyHeld(SDL_SCANCODE_E))
		{
			shipPosition = shipPosition.rotate(ship, ship.get_object()->at(0), -1);
			for (int i = 0; i < shipPosition.get_columns(); i++)
			{
				ship.get_object()->at(i).setX(shipPosition.getValue(0, i));
				ship.get_object()->at(i).setY(shipPosition.getValue(1, i));
				ship.get_object()->at(i).setZ(shipPosition.getValue(2, i));
			}
		}

		if (planetincrease)
		{
			if (ticks % 200 == 0)
				planetincrease = false;
			planetpulse = 1.0005;
		}
		else
		{
			if (ticks % 200 == 0)
				planetincrease = true;			
			planetpulse = 0.9995;
		}
		
		planetPosition = planetPosition.scale(planet, planetpulse, planetpulse, planetpulse);
		for (int i = 0; i < planetPosition.get_columns(); i++)
		{
			planet.get_object()->at(i).setX(planetPosition.getValue(0, i));
			planet.get_object()->at(i).setY(planetPosition.getValue(1, i));
			planet.get_object()->at(i).setZ(planetPosition.getValue(2, i));
		}
		for (int i = 0; i < shipPosition.get_columns(); i++)
		{
			ship.get_object()->at(i).setX(shipPosition.getValue(0, i));
			ship.get_object()->at(i).setY(shipPosition.getValue(1, i));
			ship.get_object()->at(i).setZ(shipPosition.getValue(2, i));
		}
	}
}
