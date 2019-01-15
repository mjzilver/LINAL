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
	SpaceShip ship2{ startLocation };
	SpaceShip ship3{ startLocation };
	Point planetLocation{ 800, 200, 300 };
	Planet planet{ planetLocation };
	double planetpulse = 1;
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
		render.DrawObject(&ship2);
		render.DrawObject(&ship3);
		render.DrawObject(&planet);

		render.Draw();
		Matrix shipPosition{ ship };
		Matrix shipPosition2{ ship2 };
		Matrix planetPosition{ planet };

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

			planetPosition = planetPosition.rotate(planet, planet.get_source(), 90);
			for (int i = 0; i < planetPosition.get_columns(); i++)
			{
				planet.get_object()->at(i).setX(planetPosition.getValue(0, i));
				planet.get_object()->at(i).setY(planetPosition.getValue(1, i));
				planet.get_object()->at(i).setZ(planetPosition.getValue(2, i));
			}
			scaled = true;
		}

		if (planetincrease)
		{
			if (planetpulse >= 1.01)
				planetincrease = false;
			planetpulse += 0.0001;
		}
		else
		{
			if (planetpulse <= 0.99)
				planetincrease = true;
			planetpulse -= 0.0001;
		}
		std::cout << planetpulse << std::endl;
		planetPosition = planetPosition.scale(planet, planetpulse, planetpulse, planetpulse);
		for (int i = 0; i < planetPosition.get_columns(); i++)
		{
			planet.get_object()->at(i).setX(planetPosition.getValue(0, i));
			planet.get_object()->at(i).setY(planetPosition.getValue(1, i));
			planet.get_object()->at(i).setZ(planetPosition.getValue(2, i));
		}
	}
}
