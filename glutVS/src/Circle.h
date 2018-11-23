#pragma once

#include "Color3ub.h"
#include "Vector3.h"

#include "Animation.h"

class Circle : public Animation
{
public:
	Circle(const Vector3& position, double radius, AnimationTextures textures);
	Circle(const Vector3& position, double radius, Color3ub color);
	~Circle();

	virtual void draw(void) const;

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

