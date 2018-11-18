#pragma once

#include <map>
#include <vector>

#include "Vector2.h"

struct WayPoint {
	Vector2 main;
	std::vector<Vector2> others;

	std::vector<Vector2> getAll(){
		std::vector<Vector2> all = others;
		all.push_back(main);
		return all;
	}
};

struct Route {
	Vector2 point;
	double distance;
};

// container for unique points combined with collection of all connected points
using Connection = std::map<Vector2, std::vector<Vector2>>;