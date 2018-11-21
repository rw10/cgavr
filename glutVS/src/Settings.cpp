#include "pch.h"

#include "Settings.h"

const std::string Settings::ProjectName = std::string("GLUT Project");
const double Settings::WallHeight = 5;
const double Settings::WallWidth = 0.15;
const double Settings::PlayerRadius = 3;
const double Settings::TextureSizeMultiplier = 10;

WallDisplay Settings::wayPointWalls = WallDisplay(true, Color3ub(0, 0, 127));
WallDisplay Settings::autoRouteWalls = WallDisplay(true, Color3ub(0, 255, 127));
WallDisplay Settings::lvl1RouteWalls = WallDisplay(false, Color3ub(0, 127, 0));
WallDisplay Settings::lvl1DeniedRouteWalls = WallDisplay(false, Color3ub(127, 0, 0));
WallDisplay Settings::lvl2RouteWalls = WallDisplay(true, Color3ub(0, 255, 0));
WallDisplay Settings::lvl2DeniedRouteWalls = WallDisplay(false, Color3ub(255, 0, 0));