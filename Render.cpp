#include "Render.h"
#include "Vector.h"

#include <SDL.h>
#undef main

// graphics
//1024 × 768
const char* _name = "Lineair Algebra";
const int _screenHeight = 768;
const int _screenWidth = 1024;

Render::Render()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(_screenWidth, _screenHeight, 0, &this->_window, &this->_renderer);

	SDL_SetWindowTitle(this->_window, _name);
}

void Render::DrawSquare(int x, int y, int width, int height, int r, int g, int b) const {

	SDL_SetRenderDrawColor(this->_renderer, r, g, b, 0);

	SDL_Rect rect{ rect.x = x, rect.y = y, rect.w = width, rect.h = height };
	SDL_RenderFillRect(this->_renderer, &rect);
}

void Render::DrawLine(int x, int y, int x2, int y2, int r, int g, int b) const
{
	SDL_SetRenderDrawColor(this->_renderer, r, g, b, 0);

	SDL_RenderDrawLine(this->_renderer, x, y, x2, y2);
}

void Render::DrawLine(Vector v1, Vector v2, Camera cam, int red, int green, int blue) const
{
	Vector a = (cam.getProjectionMatrix() * cam.getViewMatrix()).multiplyVector(v1);
	Vector b = (cam.getProjectionMatrix() * cam.getViewMatrix()).multiplyVector(v2);

	a.setX((_screenWidth / 2) + (a.getX() / a.getW() * (_screenWidth / 2)));
	a.setY((_screenHeight / 2) + (a.getY() / a.getW() * (_screenHeight / 2)));

	b.setX((_screenWidth / 2) + (b.getX() / b.getW() * (_screenWidth / 2)));
	b.setY((_screenHeight / 2) + (b.getY() / b.getW() * (_screenHeight / 2)));

	if (a.getW() == 1)
		DrawLine(a.getX(), a.getY(), b.getX(), b.getY(), red, green, blue);
}


void Render::Draw() const {
	SDL_RenderPresent(this->_renderer);	
}

void Render::Clear() const {
	// Black background
	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 0);
	SDL_RenderClear(this->_renderer);
}

Render::~Render()
{
	
}


void Render::DrawObject(WorldObject * object, Camera cam)
{
	auto connections = object->get_connections();
	auto points = object->get_object();
	for(auto &connection : connections)
	{
		auto start = points->at(connection.first);
		if(start.getW() == 1)
		{
			auto connected_points = connection.second;
			for (auto &connected_point : connected_points)
			{
				Vector a = (cam.getProjectionMatrix() * cam.getViewMatrix()).multiplyVector(start);
				Vector b = (cam.getProjectionMatrix() * cam.getViewMatrix()).multiplyVector(*connected_point);

				a.setX((_screenWidth / 2) + (a.getX() / a.getW() * (_screenWidth / 2)));
				a.setY((_screenHeight / 2) + (a.getY() / a.getW() * (_screenHeight / 2)));

				b.setX((_screenWidth / 2) + (b.getX() / b.getW() * (_screenWidth / 2)));
				b.setY((_screenHeight / 2) + (b.getY() / b.getW() * (_screenHeight / 2)));

				if (connected_point->getW() >= 1)
					DrawLine(a.getX(), a.getY(), b.getX(), b.getY());
			}
		}
	}
}
