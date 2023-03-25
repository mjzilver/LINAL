#include "WorldObject.h"

Vector WorldObject::get_center()
{
	float x = 0;
	float y = 0;
	float z = 0;
	for (int i = 0; i < _points.size(); i++){
		x += _points[i].getX();
		y += _points[i].getY();
		z += _points[i].getZ();
	}

	x /= _points.size();
	y /= _points.size();
	z /= _points.size();

	return Vector(x, y, z);
}

BoundingBox WorldObject::generateBoundingBox()
{
	BoundingBox bb = BoundingBox();
	for (int i = 0; i < _points.size(); i++)
	{
        Vector& p = _points.at(i);

		if (p.getX() < bb.minX || !bb.minXSet) {
			bb.minX = p.getX();
			bb.minXSet = true;
		}
		if (p.getX() > bb.maxX || !bb.maxXSet) {
			bb.maxX = p.getX();
			bb.maxXSet = true;
		}
       
		if (p.getY() < bb.minY || !bb.minYSet) {
			bb.minY = p.getY();
			bb.minYSet = true;
		}
		if (p.getY() > bb.maxY || !bb.maxYSet) {
			bb.maxY = p.getY();
			bb.maxYSet = true;
		}

		if (p.getZ() < bb.minZ || !bb.minZSet) {
			bb.minZ = p.getZ();
			bb.minZSet = true;
		}
		if (p.getZ() > bb.maxZ || !bb.maxZSet) {
			bb.maxZ = p.getZ();
			bb.maxZSet = true;
		}
	}
	return bb;
}
