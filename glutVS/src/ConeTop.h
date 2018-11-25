#pragma once

#include "Circle.h"

class ConeTop : public Circle
{
public:
	ConeTop(const Vector3& position, double radius, double height, AnimationTextures textures) :
		Circle(position, radius, textures), height(height)
	{}
	ConeTop(const Vector3& position, double radius, double height, Color3ub color) :
		Circle(position, radius, color), height(height)
	{}

	~ConeTop(){}

protected:
	virtual GLfloat centerHeight() const {
		return (GLfloat) (pos.z + height);
	}

	virtual GLfloat circleHeight() const {
		return (GLfloat) pos.z;
	}

private:
	double height;

};

