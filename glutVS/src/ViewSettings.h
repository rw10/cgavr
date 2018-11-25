#pragma once

#include "Color3ub.h"
#include <vector>

struct WallDisplay {
	bool show;
	Color3ub color;

	WallDisplay(bool show, Color3ub color) : show(show), color(color) {}
};

class ViewSettings {
public:

	WallDisplay wayPointWalls;
	WallDisplay autoRouteWalls;
	WallDisplay lvl1RouteWalls;
	WallDisplay lvl1DeniedRouteWalls;
	WallDisplay lvl2RouteWalls;
	WallDisplay lvl2DeniedRouteWalls;
	WallDisplay additionalRouteWalls;
	WallDisplay additionalDeniedRouteWalls;
	WallDisplay dijkstraRoute;
	bool ShowAxis;

	ViewSettings();
};