#pragma once

#include <map>
#include <vector>

#include "Vector2.h"

struct Route {
	Vector2 point;
	double distance;
};

// container for unique points combined with collection of all connected points
using ConnectedNetwork = std::map<Vector2, std::vector<Vector2>>;