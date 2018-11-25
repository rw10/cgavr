#include "pch.h"

#include "Cone.h"

Cone::Cone(const Vector3& position, double radius, double height, AnimationTextures textures, double animationDuration = 1000.0) :
	Animation(textures, animationDuration), pos(position), radius(radius), height(height)
{
	floorCircle = new Circle(pos, radius, textures);
	coneTop = new ConeTop(pos, radius, height, textures);
}

Cone::Cone(const Vector3& position, double radius, double height, Color3ub color) :
	Animation(color), pos(position), radius(radius), height(height)
{
	floorCircle = new Circle(pos, radius, color);
	coneTop = new ConeTop(pos, radius, height, color);
}

Cone::~Cone() {
	delete floorCircle;
	delete coneTop;
}


void Cone::animate(const double time) {
	// bottom and coneTop
	floorCircle->animate(time);
	coneTop->animate(time);

	Animation::animate(time);
}

void Cone::draw(void) const{
	// nothing to do
	// is drawn by parts
}