#pragma once

#include "ConeTop.h"

class Cone : public Animation
{
public:
	Cone(const Vector3& position, double radius, double height, AnimationTextures textures);
	Cone(const Vector3& position, double radius, double height, Color3ub color);
	~Cone();

	virtual void draw(void) const;

	// pos = bottom center
	Vector3 pos;
	double radius;
	double height;

private:
	Circle* floorCircle;
	ConeTop* coneTop;

};

