#include "pch.h"

#include "Collision.h"

#include <math.h>

Collision::Collision()
{}

Collision::~Collision()
{}

bool Collision::isColliding(const Vector2& source, const Vector2& target, const Wall& wall){		//, double distanceToWall) {
	// compare: https://en.wikipedia.org/wiki/Line�line_intersection

	// use shorter identifiers
	const double& x1 = source.x;
	const double& y1 = source.y;
	const double& x2 = target.x;
	const double& y2 = target.y;
	const double& x3 = wall.begin.x;
	const double& y3 = wall.begin.y;
	const double& x4 = wall.end.x;
	const double& y4 = wall.end.y;

	double dx12 = x1 - x2;
	double dy12 = y1 - y2;
	double dx34 = x3 - x4;
	double dy34 = y3 - y4;	
	double divisor = dx12 * dy34 - dy12 * dx34;

	if (divisor == 0) {
		// parallel - no intersection at all
		return false;
	}

	/*
	// previous method
	// calculate point of intersection of limitless lines
	double term1 = (x1 * y2 - y1 * x2);
	double term2 = (x3 * y4 - y3 * x4);
	double px = (term1 * dx34 - dx12 * term2) / divisor;
	double py = (term1 * dy34 - dy12 * term2) / divisor;
	Vector2 intersection(px, py);
	
	// check by bounding box test
	bool collision = isPointInBoundingBox(source, target, intersection) && isPointInBoundingBox(wall.begin, wall.end, intersection);
	*/

	double distanceL = 0;		// distanceToWall / (source - target).getLength();
	double distanceU = 0;		// distanceToWall / wall.getLength();

	// check if intersection point is between the limits
	double t = ((x1 - x3) * dy34 - (y1 - y3) * dx34) / divisor;
	double u = - ((y1 - y3) * dx12 - (x1 - x3) * dy12) / divisor;
	bool collision = 
		t >= -distanceL && 
		t <= 1+distanceL && 
		u >= -distanceU && 
		u <= 1+distanceU;

	return collision;


	/*
	// calculation of intersection point
	double px = x1 + t * (x2 - x1);
	double py = y1 + t * (y2 - y1);;
	Vector2 intersection(px, py);
	*/
}


bool Collision::isPointInBoundingBox(const Vector2& p1, const Vector2& p2, const Vector2& point) {
	double lowX = fmin(p1.x, p2.x);
	double highX = fmax(p1.x, p2.x);
	double lowY = fmin(p1.y, p2.y);
	double highY = fmax(p1.y, p2.y);
	bool collision = point.x <= highX && point.x >= lowX && point.y <= highY && point.y >= lowY;

	return collision;
}


double Collision::findClosestDistance(const Vector2& source, const Vector2& target, const Wall& wall) {

	double d1 = findClosestDistance(source, target, wall.begin);
	double d2 = findClosestDistance(source, target, wall.end);

	return fmin(
		findClosestDistance(source, target, wall.begin),
		findClosestDistance(source, target, wall.end)
	);

	/*
	// faster:	
	// use shorter identifiers
	const double& x1 = source.x;
	const double& y1 = source.y;
	const double& x2 = target.x;
	const double& y2 = target.y;
	const double& x3 = wall.begin.x;
	const double& y3 = wall.begin.y;
	const double& x4 = wall.end.x;
	const double& y4 = wall.end.y;

	double dx = x2 - x1;
	double dy = y2 - y1;

	double divisor = sqrt(dy * dy + dx * dx);
	if (divisor == 0) {
		return fmin(
			(wall.begin - source).getLength(),
			(wall.end - source).getLength()
		);
	}

	double distance1 = fabs(dy * x3 - dx * y3 + x2 * y1 - y2 * x1) / divisor;
	double distance2 = fabs(dy * x4 - dx * y4 + x2 * y1 - y2 * x1) / divisor;
	return fmin(distance1, distance2);

	*/
}

double Collision::findClosestDistance(const Vector2& source, const Vector2& target, const Vector2& point) {
	return (
		Vector2::getClosestPointOnLineSegment(source, target, point) - point
	).getLength();
}
