#pragma once

#include <GL/glut.h>

class Vector3
{
public:
	Vector3();
	Vector3(double x, double y, double z);
	~Vector3();

	double _x;
	double _y;
	double _z;

	GLfloat x() {
		return (GLfloat)_x;
	}
	GLfloat y() {
		return (GLfloat)_y;
	}
	GLfloat z() {
		return (GLfloat)_z;
	}

	// overloaded operators
	Vector3 operator+ (const Vector3& other) const;
	Vector3 operator- (const Vector3& other) const;
	Vector3 operator* (const double& multiplier) const;	
	//Vector3 operator* (const Vector3& other) const;

	double getLength();
	void normalize(double targetLength = 1);

	static double deg2rad(double degrees);
	static double rad2deg(double radians);

	static Vector3 getRichtungsVector(const Vector3& begin, const Vector3& end);

	void rotateAroundX(double degrees);
	void rotateAroundY(double degrees);
	void rotateAroundZ(double degrees);

	double calcAngleInXY(const Vector3& other);
	// not needed (yet)
	//double calcAngleInXZ(const Vector3& other);
	//double calcAngleInYZ(const Vector3& other);


	// TODO:
	// normalize, multiplication, addition, rotation, angle calculation, intersection, ...

};

