#pragma once

#include <map>
#include <vector>

#include "Vector2.h"

// container for unique points combined with collection of all connected points
using Connection = std::map<Vector2, std::vector<Vector2>>;