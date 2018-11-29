#include "pch.h"

#include "Settings.h"

const std::string Settings::ProjectName = std::string("GLUT Project");
const double Settings::WallHeight = 5;
const double Settings::WallWidth = 1.15;
const double Settings::PlayerRadius = 2;
const double Settings::PlayerHeight = 3;
double Settings::PlayerSpeed = 0.3;
const double Settings::TextureSizeMultiplier = 10;

const size_t Settings::CircleDrawPrecision = 90;
const size_t Settings::WayPointDetail = 3;

// precision should be very close to 1
// too high -> more collisions than wanted, too low -> less collisions than wanted
const double Settings::CollisionPrecision = 0.9999;		 // 1 - pow(0.1, WayPointDetail + 1);

