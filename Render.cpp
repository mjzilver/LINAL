#include "Render.h"

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

void Render::DrawObject(WorldObject * object)
{
	auto connections = object->get_connections();
	auto points = object->get_object();
	for(auto &connection : connections)
	{
		auto start = points->at(connection.first);
		if(start.draw())
		{
			auto connected_points = connection.second;
			for (auto &connected_point : connected_points)
			{
				if (connected_point->draw())
					DrawLine(start.getX(), start.getY(), connected_point->getX(), connected_point->getY());
			}
		}
	}
}
