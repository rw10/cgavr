#pragma once

#include "Wall.h"

class Collision
{
public:
	static bool isColliding(const Vector2& source, const Vector2& target, const Wall& wall);
	static double findClosestDistance(const Vector2& source, const Vector2& target, const Wall& wall);

private:
	static bool isPointInBoundingBox(const Vector2& source, const Vector2& target, const Vector2& point);
	static double findClosestDistance(const Vector2& p1, const Vector2& p2, const Vector2& point);

	Collision();
	~Collision();

};