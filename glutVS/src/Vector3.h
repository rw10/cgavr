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

	GLfloat gl_x() {
		return (GLfloat)x;
	}
	GLfloat gl_y() {
		return (GLfloat)y;
	}
	GLfloat gl_z() {
		return (GLfloat)z;
	}

	// compare operator
	bool operator< (const Vector3& other) {
		return x == other.x ?
			y == other.y ?
			z < other.z :
			y < other.y :
			x < other.x;
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

	double distance(const Vector3& other) const;
	static double distance(const Vector3& start, const Vector3& end) {
		start.distance(end);
	}

	static double calcAngleInXY(Vector3 u, Vector3 v);
	static double dotProduct(const Vector3& u, const Vector3& v);



	// not needed (yet)
	//double calcAngleInXZ(const Vector3& other);
	//double calcAngleInYZ(const Vector3& other);


	// TODO:
	// normalize, multiplication, addition, rotation, angle calculation, intersection, ...

};

