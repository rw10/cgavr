#pragma once

#include "Color3ub.h"
#include "Vector3.h"

#include "Animation.h"

class Circle : public Animation
{
public:
	Circle(const Vector3& position, double radius, AnimationTextures textures, double animationDuration = 1000.0);
	Circle(const Vector3& position, double radius, Color3ub color);
	~Circle();

	Vector3 pos;
	double radius;

protected:
	virtual void draw(void) const;

	virtual GLfloat centerHeight() const {
		return (GLfloat) pos.z;
	}

	virtual GLfloat circleHeight() const {
		return (GLfloat) pos.z;
	}
};

