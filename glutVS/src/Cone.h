#pragma once

#include "ConeTop.h"

class Cone : public Animation
{
public:
	Cone(const Vector3& position, double radius, double height, AnimationTextures textures, double animationDuration);
	Cone(const Vector3& position, double radius, double height, Color3ub color);
	~Cone();

	virtual void animate(const double time);

protected:
	virtual void draw(void) const;

private:
	Circle* floorCircle;
	ConeTop* coneTop;

	// pos = bottom center
	Vector3 pos;
	double radius;
	double height;

};

