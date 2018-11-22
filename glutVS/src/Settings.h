#pragma once

#include <string>
#include "Color3ub.h"

struct WallDisplay {
	bool show;
	Color3ub color;

	WallDisplay(bool show, Color3ub color) : show(show), color(color) {}
};

class Settings {
public:
	static const std::string ProjectName;
	static const double WallHeight;
	static const double WallWidth;
	static const double PlayerRadius;
	static const double TextureSizeMultiplier;
	// how many points to use for drawing a full circle, should be a common divisor of 360
	static const size_t CircleDrawPrecision;
	static bool ShowAxis;

	static WallDisplay invisibleWalls;
	static WallDisplay wayPointWalls;
	static WallDisplay autoRouteWalls;
	static WallDisplay lvl1RouteWalls;
	static WallDisplay lvl1DeniedRouteWalls;
	static WallDisplay lvl2RouteWalls;
	static WallDisplay lvl2DeniedRouteWalls;
	static WallDisplay additionalRouteWalls;
	static WallDisplay additionalDeniedRouteWalls;
	static WallDisplay dijkstraRoute;
};