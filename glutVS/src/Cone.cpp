

#include "Cone.h"

Cone::Cone(const Vector3& position, double radius, double height, AnimationTextures textures, double animationDuration = 1000.0) :
	Animation(textures, animationDuration), pos(position), radius(radius), height(height)
{
	floorCircle = std::shared_ptr<Circle>(new Circle(pos, radius, textures));
	coneTop = std::shared_ptr<ConeTop>(new ConeTop(pos, radius, height, textures));
}

Cone::Cone(const Vector3& position, double radius, double height, Color3ub color) :
	Animation(color), pos(position), radius(radius), height(height)
{
	floorCircle = std::shared_ptr<Circle>(new Circle(pos, radius, color));
	coneTop = std::shared_ptr<ConeTop>(new ConeTop(pos, radius, height, color));
}

Cone::~Cone() {}


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