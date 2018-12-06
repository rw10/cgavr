#pragma once



#include <string>

class Settings {
public:
	static const std::string ProjectName;
	static const double WallHeight;
	static const double WallWidth;
	static const double PlayerRadius;
	static const double PlayerHeight;
	static double PlayerSpeed;
	static const double TextureSizeMultiplier;
	static size_t UpdateInterval;
	static size_t DrawInterval;

	static const double CameraMovementSpeed;
	static const double CameraRotationSpeed;

	static const double CollisionPrecision;
	
	// how many points to use for drawing a full circle, should be a common divisor of 360
	static const size_t CircleDrawPrecision;

	// how many points to use for a waypoint
	// 0 = 3 points around corner
	// 1 = 5 points around corner
	// 2 = 7 ....
	static const size_t WayPointDetail;
};