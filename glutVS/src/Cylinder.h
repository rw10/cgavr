#pragma once

#include "Animation.h"

#include "Color3ub.h"
#include "Vector3.h"
#include "Circle.h"

#include <memory>


class Cylinder : public Animation
{
public:
	Cylinder(const Vector3& position, double radius, double height, AnimationTextures textures, bool fillTexture = true, double animationDuration = 1000.0);
	Cylinder(const Vector3& position, double radius, double height, Color3ub color);
	Cylinder() : Animation(Color3ub(0, 0, 0)) {}
	~Cylinder();

	virtual void animate(const double time);

	void setStartAngle(int angle) {
		startAngle = angle;
		floorCircle->setStartAngle(angle);
		ceilingCircle->setStartAngle(angle);
	}
	void setEndAngle(int angle) {
		endAngle = angle;
		floorCircle->setEndAngle(angle);
		ceilingCircle->setEndAngle(angle);
	}

protected:
	virtual void draw(void) const;

	int startAngle = 0;
	int endAngle = 360;

private:
	void init();

	void createVertex(int angle) const;
	void createCenterVertex(int angle) const;

	// make texture use virtual world sizes instead of stretching
	GLfloat textureSizeX;
	GLfloat textureSizeY;

	// pos = bottom center
	Vector3 pos;
	double radius;
	double height;

	std::shared_ptr<Circle> floorCircle;
	std::shared_ptr<Circle> ceilingCircle;

};

