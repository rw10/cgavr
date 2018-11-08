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


	// multiplication, addition, ...

};

