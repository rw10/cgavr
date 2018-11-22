#pragma once

#include <GL/glut.h>

class Vector3
{
public:
	Vector3();
	Vector3(double x, double y, double z);
	~Vector3();

	double x;
	double y;
	double z;

	GLfloat gl_x() const {
		return (GLfloat)x;
	}
	GLfloat gl_y() const {
		return (GLfloat)y;
	}
	GLfloat gl_z() const {
		return (GLfloat)z;
	}

	// compare operator
	bool operator< (const Vector3& other) const;
	bool operator!= (const Vector3& other) const;

	// overloaded operators
	Vector3 operator+ (const Vector3& other) const;
	Vector3 operator- (const Vector3& other) const;
	Vector3 operator*(const Vector3& other) const;		// cross product
	Vector3 operator* (const double& multiplier) const;	// multiplication with scalar


	static double dotProduct(const Vector3& u, const Vector3& v);
	static double calcAngleInXY(Vector3 u, Vector3 v);
	// not needed (yet)
	//static double calcAngleInXZ(Vector3 u, Vector3 v);
	//static double calcAngleInYZ(Vector3 u, Vector3 v);

	double getLength() const;
	double getLengthXY() const;

	void normalize(double targetLength = 1);

	static double deg2rad(double degrees);
	static double rad2deg(double radians);

	static Vector3 getRichtungsVector(const Vector3& begin, const Vector3& end);

	void rotateAroundX(double degrees);
	void rotateAroundY(double degrees);
	void rotateAroundZ(double degrees);

	double distance(const Vector3& other) const;
	static double distance(const Vector3& start, const Vector3& end) {
		start.distance(end);
	}





	// TODO:
	// normalize, multiplication, addition, rotation, angle calculation, intersection, ...

};

