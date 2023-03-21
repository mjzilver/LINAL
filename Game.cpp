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

	targets.push_back(std::make_shared<Target>(Vector{ 800, 400, 10 }));
	targets.push_back(std::make_shared<Target>(Vector{ 100, 250, 10 }));
	targets.push_back(std::make_shared<Target>(Vector{ 800, 200, 30 }));

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
			render.DrawObject(bullets.at(i).get(), camera);
		}

		for (std::shared_ptr<Target> t : targets) {
			render.DrawObject(t.get(), camera);
		}

		render.DrawObject(&ship, camera);
		if (printHelperLine) {
			Vector shipcenter = ship.get_center();
			render.DrawLine(shipcenter.getX(), shipcenter.getY(), shipcenter.getX() + ship.force.getX() * 1000, shipcenter.getY() + ship.force.getY() * 1000, 255, 0, 0);
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
			camera.lookat.setY((camera.lookat.getY() - 10));
		}
		if (input.wasKeyReleased(SDL_SCANCODE_PAGEDOWN)) {
			camera.lookat.setY((camera.lookat.getY() + 10));
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
		}

		// All update cycles under here
		// ship update
		ship.update();
		
		// alle coords moeten lokaal zijn dus en niet in de eigen wereld 
		// de camera transformatie moet eenmalig gedaan worden en dus alleen effect hebben op de getekende punten maar NIET op de reële punten in de coordinaten 
		// dus bij het tekenen word de camera transformatie matrix toegepast maar niet op de coordinaten
		// dit allemaal in de renderer doen zoiets van 
		// get transformation matrix
		// get connections
		// transform connections
		// draw transformed connections
		// good luck!


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

			// bullet goes off screen - delete bullet
			if (b->get_point(0).getX() > 1024 || b->get_point(0).getX() < 0 || b->get_point(0).getY() > 768 || b->get_point(0).getY() < 0) {
				bullets.erase(bullets.begin() + i);
			}

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
