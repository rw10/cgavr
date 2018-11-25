#pragma once

#include "Animation.h"

#include "Color3ub.h"
#include "Vector3.h"
#include "Circle.h"


class Cylinder : public Animation
{
public:
	Cylinder(const Vector3& position, double radius, double height, AnimationTextures textures, double animationDuration = 1000.0);
	Cylinder(const Vector3& position, double radius, double height, Color3ub color);
	~Cylinder();

	virtual void animate(const double time);

protected:
	virtual void draw(void) const;

private:
	// pos = bottom center
	Vector3 pos;
	double radius;
	double height;

	Circle* floorCircle;
	Circle* ceilingCircle;

};

