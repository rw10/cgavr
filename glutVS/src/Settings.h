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
	// how many points to use for drawing a full circle, should be a common divisor of 360
	static const size_t CircleDrawPrecision;
};