#include "Game.h"

#undef main

void Game::StartGameLoop()
{
	SDL_Event SDL_event;
	SpaceShip ship{ Vector{ 400, 400, 10} };
	bool printHelperLine = false;
	bool cameraIsShip = false;
	bool cameraIsStationary = false;

	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<std::shared_ptr<Target>> targets;

	targets.push_back(std::make_shared<Target>(Vector{ 600, 410, 10 }));
	targets.push_back(std::make_shared<Target>(Vector{ 100, 250, 300 }));
	targets.push_back(std::make_shared<Target>(Vector{ 930, 400, -30 }));
	targets.push_back(std::make_shared<Target>(Vector{ 300, 300, 250 }));
	targets.push_back(std::make_shared<Target>(Vector{ 600, 200, 0 }));
	targets.push_back(std::make_shared<Target>(Vector{ 400, 880, -100 }));
	targets.push_back(std::make_shared<Target>(Vector{ 310, 10, -250 }));

	MessageBox(HWND_DESKTOP, "Welcome to spaceship shooter 3D by Jari Zilverentant \n\nHere are the special controls\nX = toggle spaceship camera\nY = toggle stationary camera\n", "Welcome", MB_OK);


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
			render.DrawObject(*bullets.at(i).get(), camera);
		}

		for (std::shared_ptr<Target> t : targets) {
			render.DrawObject(*t.get(), camera);
		}

		render.DrawObject(*&ship, camera);
		if (printHelperLine) {
			Vector lineStart = ship.get_center() + ship.get_coordinates();
			Vector lineEnd = lineStart + (ship.force * 1000);
			render.DrawLine(lineStart, lineEnd, camera, 255, 0, 0);
		}
		render.Draw();

		// inputs
		if(input.isKeyHeld(SDL_SCANCODE_LSHIFT))
			ship.speedUp();

		if (input.isKeyHeld(SDL_SCANCODE_UP)) {
			camera.eye.setY(camera.eye.getY() - 1);
		}
		if (input.isKeyHeld(SDL_SCANCODE_DOWN)) {
			camera.eye.setY(camera.eye.getY() + 1);
		}
		if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			camera.eye.setX(camera.eye.getX() + 1);
		}
		if (input.isKeyHeld(SDL_SCANCODE_LEFT)) {
			camera.eye.setX(camera.eye.getX() - 1);
		}
		if (input.wasKeyReleased(SDL_SCANCODE_PAGEUP)) {
			camera.changePov(1);
		}
		if (input.wasKeyReleased(SDL_SCANCODE_PAGEDOWN)) {
			camera.changePov(-1);
		}

		// all rotational keys
		if (input.isKeyHeld(SDL_SCANCODE_Q)) {
			ship.rotate(Matrix::roll(-1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_E)) {
			ship.rotate(Matrix::roll(1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_W)) {
			ship.rotate(Matrix::pitch(1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_S)) {
			ship.rotate(Matrix::pitch(-1));
		} 
		if (input.isKeyHeld(SDL_SCANCODE_A)) {
			ship.rotate(Matrix::yaw(-1));
		}
		if (input.isKeyHeld(SDL_SCANCODE_D)) {
			ship.rotate(Matrix::yaw(1));
		}

		// toggles the helper line to show the bullet movement
		if (input.wasKeyReleased(SDL_SCANCODE_H)) {
			printHelperLine = !printHelperLine;
		}

		// space bar fires a bullet in the direction and speed of the shop
		if (input.wasKeyReleased(SDL_SCANCODE_SPACE)) {
			std::shared_ptr<Bullet> p = std::make_shared<Bullet>(ship.get_center() + ship.get_coordinates(), ship.force, ship.speed);
			bullets.push_back(p);
			// if more than 20 bullets delete one :)
			if (bullets.size() > 20) {
				bullets.erase(bullets.begin());
			}
		}

		// toggle ship POV
		if (input.wasKeyReleased(SDL_SCANCODE_X)) {
			cameraIsShip = !cameraIsShip;
			if (!cameraIsShip) {
				camera.changePov(0);
			}
		}

		if (input.wasKeyReleased(SDL_SCANCODE_Y)) {
			cameraIsStationary = !cameraIsStationary;
		}

		// if the camera is locked the ship keep it moving along
		if (!cameraIsStationary) {
			if (cameraIsShip) {
				camera.eye = ship.get_center() + ship.get_coordinates();
			}
			camera.lookat = ship.get_center() + ship.get_coordinates() + (ship.force);
		}

		// All update cycles under here
		// ship update
		ship.update();
		
		// target update
		for (std::shared_ptr<Target> t : targets) {
			t.get()->update();

			// collision with the ship
			if (BoxBoxCollision(ship.generateBoundingBox(), t.get()->generateBoundingBox())) {
				MessageBox(HWND_DESKTOP, "You crashed and died!", "You died!", MB_OK);
				gameLoop = false;
			}
		}

		if (targets.size() == 0) {
			MessageBox(HWND_DESKTOP, "All targets have been destroyed, good job!", "You won!", MB_OK);
			gameLoop = false;
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
