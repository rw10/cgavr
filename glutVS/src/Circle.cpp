

#include "Circle.h"

#include "GL/glut.h"
#include <cmath> 
#include "TextureLoader.h"
#include "Settings.h"

Circle::Circle(const Vector3& position, double radius, AnimationTextures textures, double animationDuration) :
	Animation(textures, animationDuration), pos(position), radius(radius)
{}

Circle::Circle(const Vector3& position, double radius, Color3ub color) :
	Animation(color), pos(position), radius(radius)
{}

Circle::~Circle(){}

void Circle::draw(void) const {
	// used full, stretched texture for circle instead of real world sizes
	//GLfloat textureSize = (GLfloat)(2 * radius / Settings::TextureSizeMultiplier);

	// bottom
	int step = 360 / (int) Settings::CircleDrawPrecision;
	glBegin(GL_TRIANGLE_FAN);
	// center
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f((GLfloat) pos.x, (GLfloat) pos.y, centerHeight());
	for (int i = startAngle; i < endAngle; i+=step)
	{
		// points around center
		createVertex(i);
	}
	// final point with endAngle
	createVertex(endAngle);
	glEnd();
}

void Circle::createVertex(int angle) const {
	double degree = Vector3::deg2rad((double)angle);
	double dx = cos(degree);
	double dy = sin(degree);
	glTexCoord2f((GLfloat)(dx / 2 + 0.5f), (GLfloat)(dy / 2 + 0.5f));
	glVertex3f((GLfloat)(pos.x + dx * radius), (GLfloat)(pos.y + dy * radius), circleHeight());
}
