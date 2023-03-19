#pragma once
#include <vector>
#include <map>
#include "Vector.h"

struct BoundingBox {
    float minX;
    float minY;
    float minZ;
    float maxX;
    float maxY;
    float maxZ;


    bool minXSet = false;
    bool minYSet = false;
    bool minZSet = false;
    bool maxXSet = false;
    bool maxYSet = false;
    bool maxZSet = false;

    BoundingBox(float minX = 0, float minY = 0, float minZ = 0, float maxX = 0, float maxY = 0, float maxZ = 0)
    {
        this->minX = minX;
        this->minY = minY;
        this->minZ = minZ;
        this->maxX = maxX;
        this->maxY = maxY;
        this->maxZ = maxZ;
    }
};


class WorldObject
{
public:
	WorldObject();
	~WorldObject();
	std::vector<Vector>* get_object() { return &_points; }
	std::map<int,std::vector<Vector*>> get_connections() { return _connections; }
	Vector get_source() { return _source; }
	Vector get_center();
	Vector get_point(int i) { return _points.at(i); }

    BoundingBox generateBoundingBox();

protected:
	std::map<int, std::vector<Vector*>> _connections;
	std::vector<Vector> _points;
	Vector _source;
    BoundingBox _boundingBox;
};

