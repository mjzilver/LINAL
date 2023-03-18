#include "Game.h"
#include "Render.h"
#include <iostream>

#include <SDL.h>
#include "Matrix.h"
#include "SpaceShip.h"
#include "Planet.h"
#include "Bullet.h"

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
	Point planetLocation{ 800, 400, 10 };
	Planet planet{ planetLocation };
	double planetpulse = 1;
	int ticks = 0;
	bool planetincrease = true;
	bool printHelperLine = false;

	std::vector<std::shared_ptr<Bullet>> bullets;

	bool scaled = false;

	while (gameLoop)
	{
		// input gedeelte
		input.resetKeys();
		Point shipcenter = ship.get_center();

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

		// rendering 
		render.Clear();
		for (int i = 0; i < bullets.size(); i++)
		{
			render.DrawObject(bullets.at(i).get());
		}
		render.DrawObject(&ship);
		render.DrawObject(&planet);
		if (printHelperLine)
			render.DrawLine(shipcenter.getX(), shipcenter.getY(), shipcenter.getX() + ship.force.getX() * 1000, shipcenter.getY() + ship.force.getY() * 1000, 255, 0, 0);
		render.Draw();
		Matrix planetPosition{ planet };
		Matrix shipPosition{ ship };

		ticks++;
		// inputs
		if(input.isKeyHeld(SDL_SCANCODE_LSHIFT))
		{
			if (ship.speed < 0.5)
				ship.speed += 0.005f;
		} else 	if (input.isKeyHeld(SDL_SCANCODE_LALT))
		{
			if (ship.speed < 0)
				ship.speed -= 0.005f;
		}

		Matrix relative = shipPosition.getRelative(shipcenter);
		Matrix rotation = Matrix(4, 4);

		if (input.isKeyHeld(SDL_SCANCODE_Q)) {
			rotation = relative.roll(1);
			ship.force = rotation.multiplyVector(ship.force);
			relative = rotation* relative;
			shipPosition = relative.getAbsolute(shipcenter);
		}
		if (input.isKeyHeld(SDL_SCANCODE_E)) {
			rotation = relative.roll(-1);
			ship.force = rotation.multiplyVector(ship.force);
			relative = rotation * relative;
			shipPosition = relative.getAbsolute(shipcenter);
		}
		if (input.isKeyHeld(SDL_SCANCODE_W)) {
			rotation = relative.pitch(1);
			ship.force = rotation.multiplyVector(ship.force);
			relative = rotation * relative;
			shipPosition = relative.getAbsolute(shipcenter);
		}
		if (input.isKeyHeld(SDL_SCANCODE_S)) {
			rotation = relative.pitch(-1);
			ship.force = rotation.multiplyVector(ship.force);
			relative = rotation * relative;
			shipPosition = relative.getAbsolute(shipcenter);
		} 
		if (input.isKeyHeld(SDL_SCANCODE_A)) {
			rotation = relative.yaw(1);
			ship.force = rotation.multiplyVector(ship.force);
			relative = rotation * relative;
			shipPosition = relative.getAbsolute(shipcenter);
		}
		if (input.isKeyHeld(SDL_SCANCODE_D)) {
			rotation = relative.yaw(-1);
			ship.force = rotation.multiplyVector(ship.force);
			relative = rotation * relative;
			shipPosition = relative.getAbsolute(shipcenter);
		}

		// toggles the helper line to show the bullet movement
		if (input.wasKeyReleased(SDL_SCANCODE_H)) {
			printHelperLine = !printHelperLine;
		}

		// space bar fires a bullet in the direction and speed of the shop
		if (input.wasKeyReleased(SDL_SCANCODE_SPACE)) {
			std::shared_ptr<Bullet> p = std::make_shared<Bullet>(ship.get_center(), ship.force, ship.speed);
			bullets.push_back(p);
		}


		// spaceship movement
		shipPosition = shipPosition.translate(
			ship.force.getX() * ship.speed,
			ship.force.getY() * ship.speed,
			ship.force.getZ() * ship.speed) * shipPosition;

		if (ship.speed > 0.00f)
			ship.speed -= 0.001f;
		else if (ship.speed < 0.0f)
			ship.speed = 0.0f;

		// planet movement 
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

		// collision
		for (int i = 0; i < shipPosition.get_columns(); i++)
		{
			Point shipPoint = ship.get_object()->at(i);
			for (int j = 0; j < planetPosition.get_columns(); j++)
			{
				Point planetPoint = planet.get_object()->at(j);
				if ((abs(shipPoint.getX() - planetPoint.getX()) < 25)
					&& (abs(shipPoint.getY() - planetPoint.getY()) < 25)
					&& (abs(shipPoint.getZ() - planetPoint.getZ()) < 25))
				{
					std::cout << "COLLISION!!!!" << std::endl;
				}
			}
		}

		// bullet movement and such
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets.at(i)->update();

			if (bullets.at(i)->get_point(0).getX() > 1024 || bullets.at(i)->get_point(0).getX() < 0
				|| bullets.at(i)->get_point(0).getY() > 768 || bullets.at(i)->get_point(0).getY() < 0) {
				bullets.erase(bullets.begin() + i);
			}
		}
	}
}
