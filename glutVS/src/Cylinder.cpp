#include "pch.h"

#include "Cylinder.h"

#include "GL/glut.h"
#include "TextureLoader.h"
#include "Settings.h"
#include "Constants.h"

#include <cmath>

Cylinder::Cylinder(const Vector3& position, double radius, double height, AnimationTextures textures, double animationDuration) :
	Animation(textures, animationDuration), pos(position), radius(radius), height(height)
{
	floorCircle = std::shared_ptr<Circle> (new Circle(pos, radius, textures));

	Vector3 cPos = pos;
	cPos.z += height;
	ceilingCircle = std::shared_ptr<Circle>(new Circle(cPos, radius, textures));
	init();
}

Cylinder::Cylinder(const Vector3& position, double radius, double height, Color3ub color) :
	Animation(color), pos(position), radius(radius), height(height)
{
	floorCircle = std::shared_ptr<Circle>(new Circle(pos, radius, color));

	Vector3 cPos = pos;
	cPos.z += height;
	ceilingCircle = std::shared_ptr<Circle>(new Circle(cPos, radius, color));
	init();
}

Cylinder::~Cylinder() {
	init();
}

void Cylinder::animate(const double time) {
	// top and bottom
	//floorCircle->animate(time);
	//ceilingCircle->animate(time);

	Animation::animate(time);
}

void Cylinder::draw(void) const {
	// --- draw the side ---
	 
	// flag to toggle texture left/right orientation
	// used when repeated texturing
	//bool lr_flag = false;

	int step = 360 / Settings::CircleDrawPrecision;
	glBegin(GL_QUAD_STRIP);
	// center point is the start
	createCenterVertex(startAngle);
	for (int i = startAngle; i < endAngle; i += step)
	{
		// points around center with radius-distance
		createVertex(i);
	}
	// final point with (exactly) endAngle
	createVertex(endAngle);
	// center point is the end
	createCenterVertex(endAngle);


	glEnd();
}

void Cylinder::createVertex(int angle) const {
	GLfloat floor = (GLfloat)pos.z;
	GLfloat ceiling = (GLfloat)(floor + height);

	double degree = Vector3::deg2rad((double)angle);
	GLfloat x = (GLfloat)(pos.x + cos(degree) * radius);
	GLfloat y = (GLfloat)(pos.y + sin(degree) * radius);
	// lower point
	glTexCoord2f((GLfloat)(angle * textureSizeX), 0.0f);
	glVertex3f(x, y, floor);
	// upper point
	glTexCoord2f((GLfloat)(angle * textureSizeX), textureSizeY);
	glVertex3f(x, y, ceiling);
}

void Cylinder::createCenterVertex(int angle) const {
	GLfloat floor = (GLfloat)pos.z;
	GLfloat ceiling = (GLfloat)(floor + height);

	GLfloat textureX = (GLfloat)(radius / Settings::TextureSizeMultiplier);

	GLfloat x = (GLfloat)(pos.x);
	GLfloat y = (GLfloat)(pos.y);
	// lower point
	glTexCoord2f((GLfloat)(angle * textureSizeX + textureX), 0.0f);
	glVertex3f(x, y, floor);
	// upper point
	glTexCoord2f((GLfloat)(angle * textureSizeX + textureX), textureSizeY);
	glVertex3f(x, y, ceiling);
}

void Cylinder::init() {
	textureSizeX = (GLfloat)(2 * Constants::PI * radius / 360 / Settings::TextureSizeMultiplier);
	textureSizeY = (GLfloat)(height / Settings::TextureSizeMultiplier);
}