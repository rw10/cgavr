#include "pch.h"
#include "Color3ub.h"

#include <math.h>


Color3ub::Color3ub(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) :
	r(red), g(green), b(blue), a(alpha)
{
}

Color3ub::Color3ub() {
}

Color3ub::~Color3ub()
{
}

Color3ub Color3ub::operator*(const double& multiplier) const
{
	return Color3ub(
		(unsigned char)fmin(255, r * multiplier),
		(unsigned char)fmin(255, g * multiplier),
		(unsigned char)fmin(255, b * multiplier),
		(unsigned char)fmin(255, a * multiplier)
	);
}
