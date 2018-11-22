#pragma once

#include "Circle.h"

class ConeTop : public Circle
{
public:
	ConeTop(const Vector3& position, double radius, double height, GLuint texture) :
		Circle(position, radius, texture), height(height)
	{}
	ConeTop(const Vector3& position, double radius, double height, Color3ub color) :
		Circle(position, radius, color), height(height)
	{}

	~ConeTop(){}

	double height;

protected:
	virtual GLfloat centerHeight() const {
		return (GLfloat) height;
	}

	virtual GLfloat circleHeight() const {
		return (GLfloat) pos.z;
	}

};

