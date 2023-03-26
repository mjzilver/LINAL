#pragma once

#include <SDL.h>
#include "Vector.h"
#include "WorldObject.h"
#include "Camera.h"

// this makes SDL work
#undef main

struct SDL_Window;
struct SDL_Renderer;

class Render
{
public:
	Render();

	void DrawLine(float x, float y, float x2, float y2, int r = 255, int g = 255, int b = 255) const;
	// draw a line between two vectors
	void DrawLine(Vector v1, Vector v2, Camera cam, int r = 255, int g = 255, int b = 255) const;

	// Renders everything to the screen
	void Draw() const;

	// Clears the screen
	void Clear() const;

	// draw object with camera angels
	void DrawObject(WorldObject &object, Camera cam);

private:
	SDL_Window* _window{};
	SDL_Renderer* _renderer{};
};