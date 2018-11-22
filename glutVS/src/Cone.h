#pragma once

#include "ConeTop.h"

class Cone : public Drawable
{
public:
	Cone(const Vector3& position, double radius, double height, GLuint texture);
	Cone(const Vector3& position, double radius, double height, Color3ub color);
	~Cone();

	virtual void draw(void) const;

	Color3ub color;
	GLuint texture;

	// pos = bottom center
	Vector3 pos;
	double radius;
	double height;

private:
	Circle* floorCircle;
	ConeTop* coneTop;

};

