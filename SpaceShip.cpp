#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Point start)
{
	_startingPoint = start;
	SDL_Point point1{start.x+20,start.y-20};
	SDL_Point point2{ start.x+120,start.y-20 };
	SDL_Point point3{ start.x+120,start.y+20 };
	SDL_Point point4{ start.x+100,start.y };
	SDL_Point point5{ start.x+100,start.y+40 };
	SDL_Point point6{ start.x,start.y+40 };

	_points.push_back(start);
	_points.push_back(point1);
	_points.push_back(point2);
	_points.push_back(point3);
	_points.push_back(point4);
	_points.push_back(point5);
	_points.push_back(point6);


	_connections[0].push_back(point1);
	_connections[0].push_back(point6);
	_connections[0].push_back(point4);
	_connections[2].push_back(point1);
	_connections[2].push_back(point4);
	_connections[2].push_back(point3);
	_connections[5].push_back(point3);
	_connections[5].push_back(point6);
	_connections[5].push_back(point4);
}

SpaceShip::~SpaceShip()
{
}
