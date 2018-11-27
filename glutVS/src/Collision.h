#pragma once

#include "Wall.h"
#include <vector>

enum CollisionTestType {
	VISIBILITY, WALL_WIDTH_ONLY, FULL_CHECK
};

class Collision
{
public:
	static bool isColliding(const Vector2& source, const Vector2& target, const std::vector<Wall>& walls, CollisionTestType type);

private:
	static bool isColliding(const Vector2& source, const Vector2& target, const Wall& wall);

	static double closestDistanceToWall(const Vector2& source, const Vector2& target, const Wall& wall);
	static double closestDistanceToPoint(const Vector2& p1, const Vector2& p2, const Vector2& point);

	static bool isPointInBoundingBox(const Vector2& source, const Vector2& target, const Vector2& point);

	Collision();
	~Collision();

};