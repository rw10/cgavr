#include "pch.h"

#include "Cone.h"

Cone::Cone(const Vector3& position, double radius, double height, AnimationTextures textures) :
	Animation(textures), pos(position), radius(radius), height(height)
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

void Cone::draw(void) const{
	// bottom and coneTop
	floorCircle->draw();
	coneTop->draw();
}