#include "Settings.h"

const std::string Settings::ProjectName = std::string("Maze Racer");
const double Settings::WallHeight = 10;
const double Settings::WallWidth = 1.15;
const double Settings::PlayerRadius = 2;
const double Settings::PlayerHeight = 3;
double Settings::PlayerSpeed = 0.05;
const double Settings::TextureSizeMultiplier = 10;
size_t Settings::UpdateInterval = 5;
size_t Settings::DrawInterval = 16;
const double Settings::CameraMovementSpeed = 0.1;
const double Settings::CameraRotationSpeed = 0.1;

const size_t Settings::CircleDrawPrecision = 90;
const size_t Settings::WayPointDetail = 3;

// precision should be very close to 1
// too high -> more collisions than wanted, too low -> less collisions than wanted
const double Settings::CollisionPrecision = 0.9999;		 // 1 - pow(0.1, WayPointDetail + 1);

