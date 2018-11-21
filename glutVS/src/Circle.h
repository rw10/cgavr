#pragma once

#include "Color3ub.h"
#include "Vector3.h"

#include "Drawable.h"

class Circle : public Drawable
{
public:
	Circle(const Vector3& position, double radius, GLuint texture);
	Circle(const Vector3& position, double radius, Color3ub color);
	~Circle();

	virtual void draw(void);

	Color3ub color;
	GLuint texture;
	Vector3 pos;
	double radius;

protected:
	virtual GLfloat centerHeight() {
		return (GLfloat) pos.z;
	}

	virtual GLfloat circleHeight() {
		return (GLfloat) pos.z;
	}

};

