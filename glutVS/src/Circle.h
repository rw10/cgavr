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

	virtual void draw(void) const;

	Color3ub color;
	GLuint texture;
	Vector3 pos;
	double radius;

protected:
	virtual GLfloat centerHeight() const {
		return (GLfloat) pos.z;
	}

	virtual GLfloat circleHeight() const {
		return (GLfloat) pos.z;
	}

};

