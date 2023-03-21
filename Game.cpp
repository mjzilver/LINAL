#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <algorithm>
#include <SDL.h>

#include "Game.h"
#include "Render.h"
#include "Matrix.h"
#include "Camera.h"
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
	bool printHelperLine = false;

	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<std::shared_ptr<Target>> targets;

	targets.push_back(std::make_shared<Target>(Vector{ 600, 410, 10 }));
	targets.push_back(std::make_shared<Target>(Vector{ 100, 250, 300 }));
	targets.push_back(std::make_shared<Target>(Vector{ 930, 400, 30 }));
	targets.push_back(std::make_shared<Target>(Vector{ 300, 300, 250 }));
	targets.push_back(std::make_shared<Target>(Vector{ 600, 200, 0 }));
	targets.push_back(std::make_shared<Target>(Vector{ 400, 880, 300 }));

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
			render.DrawObject(bullets.at(i).get(), camera);
		}

		for (std::shared_ptr<Target> t : targets) {
			render.DrawObject(t.get(), camera);
		}

		render.DrawObject(&ship, camera);
		if (printHelperLine) {
			Vector lineStart = ship.get_center();
			Vector lineEnd = Vector(lineStart.getX() + ship.force.getX() * 1000, lineStart.getY() + ship.force.getY() * 1000, lineStart.getZ() + ship.force.getZ(), lineStart.getW());
			render.DrawLine(lineStart, lineEnd, camera, 255, 0, 0);
		}
		render.Draw();

		// inputs
		if(input.isKeyHeld(SDL_SCANCODE_LSHIFT))
			ship.speedUp();

		if (input.wasKeyReleased(SDL_SCANCODE_UP)) {
			camera.eye.setY(camera.eye.getY() - 10);
		}
		if (input.wasKeyReleased(SDL_SCANCODE_DOWN)) {
			camera.eye.setY(camera.eye.getY() + 10);
		}
		if (input.wasKeyReleased(SDL_SCANCODE_RIGHT)) {
			camera.eye.setX(camera.eye.getX() + 10);
		}
		if (input.wasKeyReleased(SDL_SCANCODE_LEFT)) {
			camera.eye.setX(camera.eye.getX() - 10);
		}
		if (input.wasKeyReleased(SDL_SCANCODE_PAGEUP)) {
			camera.changePov(1);
		}
		if (input.wasKeyReleased(SDL_SCANCODE_PAGEDOWN)) {
			camera.changePov(-1);
		}

		// all rotational keys
		if (input.isKeyHeld(SDL_SCANCODE_Q)) {
			ship.rotate(Matrix::roll(-0.1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_E)) {
			ship.rotate(Matrix::roll(0.1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_W)) {
			ship.rotate(Matrix::pitch(0.1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_S)) {
			ship.rotate(Matrix::pitch(-0.1));
		} 
		if (input.isKeyHeld(SDL_SCANCODE_A)) {
			ship.rotate(Matrix::yaw(-0.1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_D)) {
			ship.rotate(Matrix::yaw(0.1));
		}

		// toggles the helper line to show the bullet movement
		if (input.wasKeyReleased(SDL_SCANCODE_H)) 
			printHelperLine = !printHelperLine;

		// space bar fires a bullet in the direction and speed of the shop
		if (input.wasKeyReleased(SDL_SCANCODE_SPACE)) {
			std::shared_ptr<Bullet> p = std::make_shared<Bullet>(ship.get_center(), ship.force, ship.speed);
			bullets.push_back(p);
			// if more than 20 bullets delete one :)
			if (bullets.size() > 20) {
				bullets.erase(bullets.begin());
			}
		}

		// All update cycles under here
		// ship update
		ship.update();
		
		// target update
		for (std::shared_ptr<Target> t : targets) {
			t.get()->update();

			// collision with the ship
			if (BoxBoxCollision(ship.generateBoundingBox(), t.get()->generateBoundingBox())) {
				MessageBox(HWND_DESKTOP, "You died!", "You died!", MB_OK);

				gameLoop = false;
			}
		}

		// bullet update cycle
		for (int i = 0; i < bullets.size(); i++)
		{
			std::shared_ptr<Bullet> b = bullets.at(i);
			b->update();

			// go over all targets to do collision checks
			for (int j = 0; j < targets.size(); j++)
			{
				std::shared_ptr<Target> t = targets.at(j);

				// bullet hits planet - delete planet
				if (BoxBoxCollision(b->generateBoundingBox(), t.get()->generateBoundingBox())) {
					std::cout << "Hit!!" << std::endl;

					targets.erase(targets.begin() + j);
				}
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
