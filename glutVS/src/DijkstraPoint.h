#pragma once

#include "Vector2.h"

#include <memory>

class DijkstraPoint {
public:
	DijkstraPoint(Vector2 position) : position(position)
	{
		first = true;
		distance = 0;
	}

	DijkstraPoint(Vector2 position, std::shared_ptr<DijkstraPoint> pred) : position(position)
	{
		first = false;
		predecessor = pred;

		double delta = position.distance(predecessor->position);
		distance = predecessor->distance + delta;
	}

	Vector2 position;

	bool isFirst() const {
		return first;
	}

	double getDistance() const {
		return distance;
	}


	bool operator< (const DijkstraPoint& other) const {
		return distance < other.distance;
	}

private:
	std::shared_ptr<DijkstraPoint> predecessor;
	double distance;
	bool first;
};