#pragma once
#include <vector>
#include <SDL.h>
#include <map>

class WorldObject
{
public:
	WorldObject();
	~WorldObject();
	std::vector<SDL_Point> get_object() { return _points; }
	std::map<int,std::vector<SDL_Point>> get_connections() { return _connections; }
	SDL_Point get_startingpoint() { return _startingPoint; }

protected:
	std::map<int, std::vector<SDL_Point>> _connections;
	std::vector<SDL_Point> _points;
	SDL_Point _startingPoint;
};

