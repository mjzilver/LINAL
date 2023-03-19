#include "Game.h"
#include "Render.h"
#include <iostream>

#include <SDL.h>
#include "Matrix.h"
#include "SpaceShip.h"
#include "Target.h"
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
	SpaceShip ship{ Vector{ 400, 400, 10} };
	Target target{ Vector{ 800, 400, 10 } };
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
		render.DrawObject(&target);
		if (printHelperLine) {
			Vector shipcenter = ship.get_center();
			render.DrawLine(shipcenter.getX(), shipcenter.getY(), shipcenter.getX() + ship.force.getX() * 1000, shipcenter.getY() + ship.force.getY() * 1000, 255, 0, 0);
		}
		render.Draw();

		// inputs
		if(input.isKeyHeld(SDL_SCANCODE_LSHIFT))
			ship.speedUp();

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
		if (input.wasKeyReleased(SDL_SCANCODE_H)) 
			printHelperLine = !printHelperLine;

		// space bar fires a bullet in the direction and speed of the shop
		if (input.wasKeyReleased(SDL_SCANCODE_SPACE)) {
			std::shared_ptr<Bullet> p = std::make_shared<Bullet>(ship.get_center(), ship.force, ship.speed);
			bullets.push_back(p);
		}

		// collision
		if (BoxBoxCollision(ship.generateBoundingBox(), target.generateBoundingBox())) {
			std::cout << "You lost!" << std::endl;
			gameLoop = false;
		}

		// All update cycles under here
		// target update
		target.update();
		// ship update
		ship.update();

		// bullet update cycle
		for (int i = 0; i < bullets.size(); i++)
		{
			std::shared_ptr<Bullet> b = bullets.at(i);
			b->update();

			// bullet goes off screen - delete bullet
			if (b->get_point(0).getX() > 1024 || b->get_point(0).getX() < 0 || b->get_point(0).getY() > 768 || b->get_point(0).getY() < 0) {
				bullets.erase(bullets.begin() + i);
			}

			// bullet hits planet - delete planet
			if (BoxBoxCollision(b->generateBoundingBox(), target.generateBoundingBox())) {
				std::cout << "Hit!!" << std::endl;
				// todo remove planet
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
