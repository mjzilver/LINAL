#pragma once

#include <SDL.h>
#include "SpaceShip.h"
#undef main

struct SDL_Window;
struct SDL_Renderer;

class Render
{
public:
	Render();

	void DrawSquare(int x, int y, int width, int height, int r = 255, int g = 255, int b = 255) const;
	void DrawLine(int x, int y, int x2, int y2, int r = 255, int g = 255, int b = 255) const;
	/* void render
	 * Renders everything to the screen
	 */
	void Draw() const;

	/* void clear
	 * Clears the screen
	 */
	void Clear() const;

	~Render();
	void DrawObject(WorldObject*object);
private:
	SDL_Window* _window{};
	SDL_Renderer* _renderer{};
};