
#include "Vector3.h"
#include "Constants.h"

#include <cmath>


Vector3::Vector3(): x(0), y(0), z(0)
{
}


Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z)
{
}

Vector3::~Vector3()
{
}

double round(long double number, int precision) {
	int decimals = (int) std::pow(10, precision);
	return (double)((std::round(number * decimals)) / decimals);
}


bool Vector3::operator< (const Vector3& other) const {
	return x != other.x ? x < other.x :
		y != other.y ? y < other.y :
		z < other.z;
}

bool Vector3::operator!= (const Vector3& other) const {
	return x != other.x || y != other.y || z != other.z;
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

Vector3 Vector3::operator*(const Vector3& other) const
{
	return Vector3(
		y * other.z - other.y * z,
		z * other.x - other.z * x,
		x * other.y - other.x * y
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

double Vector3::getLength() const {
	return sqrt(x * x + y * y + z * z);
}

double Vector3::getLengthXY() const {
	return sqrt(x * x + y * y);
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
	return (degrees * Constants::PI) / 180.0;
}

double Vector3::rad2deg(double radians) {
	return (radians * 180.0) / Constants::PI;
}

double Vector3::dotProduct(const Vector3& u, const Vector3& v) {
	return u.x*v.x + u.y*v.y + u.z*v.z;
}

double Vector3::calcAngleInXY(Vector3 u, Vector3 v) {

	// normalize
	u.normalize();
	v.normalize();
	
	// dot product u * v
	// angle = acos(u*v)
	// convert radian to degrees
	// this only gives result values between 0 and 180, we need 0 to 360
	//return rad2deg(acos(dotProduct(u, v)));

	double deg = rad2deg(
		atan2(v.y, v.x) - atan2(u.y, u.x)
	);

	if (deg < 0.0) {
		deg += 360;
	}

	return deg;
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

	y = round(_y * _cos - _z * _sin, 4);
	z = round(_y * _sin + _z * _cos, 4);
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

	x = round(_x * _cos - _z * _sin, 4);
	z = round(_x * _sin + _z * _cos, 4);
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

	x = round(_x * _cos - _y * _sin, 4);
	y = round(_x * _sin + _y * _cos, 4);
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
