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
}

Cylinder::Cylinder(const Vector3& position, double radius, double height, Color3ub color) :
	Animation(color), pos(position), radius(radius), height(height)
{
	floorCircle = std::shared_ptr<Circle>(new Circle(pos, radius, color));

	Vector3 cPos = pos;
	cPos.z += height;
	ceilingCircle = std::shared_ptr<Circle>(new Circle(cPos, radius, color));
}

Cylinder::~Cylinder() {}

void Cylinder::animate(const double time) {
	// top and bottom
	floorCircle->animate(time);
	ceilingCircle->animate(time);

	Animation::animate(time);
}

void Cylinder::draw(void) const {
	// --- draw the side ---
	// z dimension
	GLfloat floor = (GLfloat)pos.z;
	GLfloat ceiling = (GLfloat)(floor + height);
	 
	// flag to toggle texture left/right orientation
	// used when repeated texturing
	//bool lr_flag = false;

	// make texture use virtual world sizes instead of stretching
	GLfloat textureSizeX = (GLfloat)(2 * Constants::PI * radius / 360 / Settings::TextureSizeMultiplier);
	GLfloat textureSizeY = (GLfloat)((ceiling - floor) / Settings::TextureSizeMultiplier);

	size_t step = 360 / Settings::CircleDrawPrecision;
	glBegin(GL_QUAD_STRIP);
	for (size_t i = 0; i <= 360; i += step)
	{
		// points around center
		double degree = Vector3::deg2rad((double)i);
		GLfloat x = (GLfloat)(pos.x + cos(degree) * radius);
		GLfloat y = (GLfloat)(pos.y + sin(degree) * radius);

		// lower point
		glTexCoord2f((GLfloat)(i * textureSizeX), 0.0f);
		glVertex3f(x, y, floor);

		// upper point
		glTexCoord2f((GLfloat)(i * textureSizeX), textureSizeY);
		glVertex3f(x, y, ceiling);
	}

	glEnd();
}