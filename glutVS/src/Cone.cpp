#include "pch.h"

#include "Cone.h"

Cone::Cone(const Vector3& position, double radius, double height, GLuint texture) :
	pos(position), radius(radius), height(height), texture(texture), color(255, 255, 255)
{
	floorCircle = new Circle(pos, radius, texture);
	coneTop = new ConeTop(pos, radius, height, texture);
}

Cone::Cone(const Vector3& position, double radius, double height, Color3ub color) :
	pos(position), radius(radius), height(height), texture(0), color(color)
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