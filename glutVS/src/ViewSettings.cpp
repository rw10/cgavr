#include "pch.h"

#include "ViewSettings.h"

/*
std::vector<ViewSettings> ViewSettings::INSTANCES = std::vector<ViewSettings>();

ViewSettings& ViewSettings::get() {
	if (INSTANCES.size() == 0) {
		INSTANCES.push_back(ViewSettings());
	}
	return INSTANCES[0];
}
*/

ViewSettings::ViewSettings() :
	wayPointWalls(WallDisplay(false, Color3ub(0, 0, 127))),
	autoRouteWalls(WallDisplay(false, Color3ub(0, 255, 127))),
	lvl1RouteWalls(WallDisplay(false, Color3ub(0, 127, 0))),
	lvl1DeniedRouteWalls(WallDisplay(false, Color3ub(127, 0, 0))),
	lvl2RouteWalls(WallDisplay(false, Color3ub(0, 255, 0))),
	lvl2DeniedRouteWalls(WallDisplay(false, Color3ub(255, 0, 0))),
	additionalRouteWalls(WallDisplay(false, Color3ub(0, 255, 50))),
	additionalDeniedRouteWalls(WallDisplay(false, Color3ub(255, 0, 50))),
	dijkstraRoute(WallDisplay(false, Color3ub(255, 255, 255))),
	ShowAxis(false)
{}