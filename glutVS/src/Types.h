#pragma once

#include <map>
#include <vector>

#include "Vector2.h"

struct WayPoint {
	Vector2 point;
	Vector2 left;
	Vector2 right;

	std::vector<Vector2> all() {
		std::vector<Vector2> points;
		points.push_back(point);
		points.push_back(left);
		points.push_back(right);
	}

	std::vector<Vector2> partnerPoints() {
		std::vector<Vector2> points;
		points.push_back(left);
		points.push_back(right);
	}
};

// container for unique points combined with collection of all connected points
using Connection = std::map<Vector2, std::vector<Vector2>>;