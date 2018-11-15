#include "pch.h"
#include "Vector3.h"

#include <cmath>

const double PI = 3.14159265359;


Vector3::Vector3(): _x(0), _y(0), _z(0)
{
}


Vector3::Vector3(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(
		_x + other._x,
		_y + other._y,
		_z + other._z
	);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(
		_x - other._x,
		_y - other._y,
		_z - other._z
	);
}

Vector3 Vector3::operator*(const double& multiplier) const
{
	return Vector3(
		_x * multiplier,
		_y * multiplier,
		_z * multiplier
	);
}

double Vector3::getLength() {
	return sqrt(_x * _x + _y * _y + _z * _z);
}

void Vector3::normalize(double targetLength) {
	double length = getLength();
	
	// prevent division by 0
	if (length == 0) {
		length = 1;
	}

	_x = _x / length * targetLength;
	_y = _y / length * targetLength;
	_z = _z / length * targetLength;
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
			other._x - _x, 
			other._y - _y
		)
	);
}

void Vector3::rotateAroundX(double degrees) {
	// copy old values
	double y = _y;
	double z = _z;

	// convert angle to radian
	double rad = deg2rad(degrees);

	// calc sin and cos
	double _sin = sin(rad);
	double _cos = cos(rad);

	_y = y * _cos - z * _sin;
	_z = y * _sin + z * _cos;
}

void Vector3::rotateAroundY(double degrees) {
	// copy old values
	double x = _x;
	double z = _z;

	// convert angle to radian
	double rad = deg2rad(degrees);

	// calc sin and cos
	double _sin = sin(rad);
	double _cos = cos(rad);

	_x = x * _cos - z * _sin;
	_z = x * _sin + z * _cos;
}

void Vector3::rotateAroundZ(double degrees) {
	// copy old values
	double x = _x;
	double y = _y;

	// convert angle to radian
	double rad = deg2rad(degrees);

	// calc sin and cos
	double _sin = sin(rad);
	double _cos = cos(rad);

	_x = x * _cos - y * _sin;
	_y = x * _sin + y * _cos;
}


Vector3 Vector3::getRichtungsVector(const Vector3& begin, const Vector3& end) {
	Vector3 rv(
		end._x - begin._x,
		end._y - begin._y,
		end._z - begin._z
	);

	return rv;
}
