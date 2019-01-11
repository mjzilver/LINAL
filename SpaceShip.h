#pragma once
#include "WorldObject.h"
class SpaceShip :
	public WorldObject
{
public:
	SpaceShip(SDL_Point start);
	~SpaceShip();
};

