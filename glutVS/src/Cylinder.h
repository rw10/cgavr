#pragma once

#include "Drawable.h"

#include "Color3ub.h"
#include "Vector3.h"
#include "Circle.h"


class Cylinder : public Drawable
{
public:
	Cylinder(const Vector3& position, double radius, double height, GLuint texture);
	Cylinder(const Vector3& position, double radius, double height, Color3ub color);
	~Cylinder();

	virtual void draw(void);

	Color3ub color;
	GLuint texture;

	// pos = bottom center
	Vector3 pos;
	double radius;
	double height;

	Circle* floorCircle;
	Circle* ceilingCircle;

};

