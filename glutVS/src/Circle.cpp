#include "pch.h"

#include "Circle.h"

#include "GL/glut.h"
#include <cmath> 
#include "TextureLoader.h"
#include "Settings.h"

Circle::Circle(const Vector3& position, double radius, AnimationTextures textures) :
	Animation(textures), pos(position), radius(radius)
{}

Circle::Circle(const Vector3& position, double radius, Color3ub color) :
	Animation(color), pos(position), radius(radius)
{}

Circle::~Circle(){}

void Circle::draw(void) const {
	// used full, stretched texture for circle instead of real world sizes
	//GLfloat textureSize = (GLfloat)(2 * radius / Settings::TextureSizeMultiplier);

	// bottom
	size_t step = 360 / Settings::CircleDrawPrecision;
	glBegin(GL_TRIANGLE_FAN);
	// center
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f((GLfloat) pos.x, (GLfloat) pos.y, centerHeight());
	for (size_t i = 0; i <= 360; i+=step)
	{
		// points around center
		double degree = Vector3::deg2rad((double) i);
		double dx = cos(degree);
		double dy = sin(degree);
		glTexCoord2f((GLfloat)(dx/2 + 0.5f), (GLfloat)(dy/2 + 0.5f));
		glVertex3f((GLfloat)(pos.x + dx * radius), (GLfloat)(pos.y + dy * radius), circleHeight());
	}
	glEnd();
}