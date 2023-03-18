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
		if (printHelperLine) {
			Point shipcenter = ship.get_center();
			render.DrawLine(shipcenter.getX(), shipcenter.getY(), shipcenter.getX() + ship.force.getX() * 1000, shipcenter.getY() + ship.force.getY() * 1000, 255, 0, 0);
		}
		render.Draw();
		Matrix planetPosition{ planet };

		ticks++;
		// inputs
		if(input.isKeyHeld(SDL_SCANCODE_LSHIFT))
		{
			ship.speedUp();
		} 

		// all rotational keys
		if (input.isKeyHeld(SDL_SCANCODE_Q)) {
			ship.rotate(Matrix::roll(0.1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_E)) {
			ship.rotate(Matrix::roll(-0.1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_W)) {
			ship.rotate(Matrix::pitch(0.1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_S)) {
			ship.rotate(Matrix::pitch(-0.1));
		} 
		if (input.isKeyHeld(SDL_SCANCODE_A)) {
			ship.rotate(Matrix::yaw(0.1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_D)) {
			ship.rotate(Matrix::yaw(-0.1));
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

		// collision
		if (BoxBoxCollision(ship.generateBoundingBox(), planet.generateBoundingBox())) {
			std::cout << "Oeps!" << std::endl;
		}

		// All update cycles under here
		// ship update
		ship.update();

		// bullet update cycle
		for (int i = 0; i < bullets.size(); i++)
		{
			std::shared_ptr<Bullet> b = bullets.at(i);
			b->update();

			if (b->get_point(0).getX() > 1024 || b->get_point(0).getX() < 0
				|| b->get_point(0).getY() > 768 || b->get_point(0).getY() < 0) {
				bullets.erase(bullets.begin() + i);
			}

			if (BoxBoxCollision(b->generateBoundingBox(), planet.generateBoundingBox())) {
				std::cout << "Hit!!" << std::endl;
			}
		}
	}
}

bool Game::BoxBoxCollision(BoundingBox a, BoundingBox b)
{
	return (a.minX <= b.maxX && a.maxX >= b.minX) &&
		(a.minY <= b.maxY && a.maxY >= b.minY) &&
		(a.minZ <= b.maxZ && a.maxZ >= b.minZ);
}
