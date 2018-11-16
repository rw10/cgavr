#include "pch.h"
#include "Vector3.h"

#include <cmath>

const double PI = 3.14159265359;


Vector3::Vector3(): x(0), y(0), z(0)
{
}


Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z)
{
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(
		x + other.x,
		y + other.y,
		z + other.z
	);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(
		x - other.x,
		y - other.y,
		z - other.z
	);
}

Vector3 Vector3::operator*(const double& multiplier) const
{
	return Vector3(
		x * multiplier,
		y * multiplier,
		z * multiplier
	);
}

double Vector3::getLength() {
	return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize(double targetLength) {
	double length = getLength();
	
	// prevent division by 0
	if (length == 0) {
		length = 1;
	}

	x = x / length * targetLength;
	y = y / length * targetLength;
	z = z / length * targetLength;
}

double Vector3::deg2rad(double degrees) {
	return (degrees * PI) / 180.0;
}

double Vector3::rad2deg(double radians) {
	return (radians * 180.0) / PI;
}

double Vector3::calcAngleInXY(const Vector3& other) {
	return rad2deg(
		atan2(
			other.x - x, 
			other.y - y
		)
	);
}

void Vector3::rotateAroundX(double degrees) {
	// copy old values
	double _y = y;
	double _z = z;

	// convert angle to radian
	double rad = deg2rad(degrees);

	// calc sin and cos
	double _sin = sin(rad);
	double _cos = cos(rad);

	y = _y * _cos - _z * _sin;
	z = _y * _sin + _z * _cos;
}

void Vector3::rotateAroundY(double degrees) {
	// copy old values
	double _x = x;
	double _z = z;

	// convert angle to radian
	double rad = deg2rad(degrees);

	// calc sin and cos
	double _sin = sin(rad);
	double _cos = cos(rad);

	x = _x * _cos - _z * _sin;
	z = _x * _sin + _z * _cos;
}

void Vector3::rotateAroundZ(double degrees) {
	// copy old values
	double _x = x;
	double _y = y;

	// convert angle to radian
	double rad = deg2rad(degrees);

	// calc sin and cos
	double _sin = sin(rad);
	double _cos = cos(rad);

	x = _x * _cos - _y * _sin;
	y = _x * _sin + _y * _cos;
}


Vector3 Vector3::getRichtungsVector(const Vector3& begin, const Vector3& end) {
	Vector3 rv(
		end.x - begin.x,
		end.y - begin.y,
		end.z - begin.z
	);
	return rv;
}


double Vector3::distance(const Vector3& other) const{
	return (*this - other).getLength();
}
