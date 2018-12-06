

#include "Circle.h"

#include "GL/glut.h"
#include <cmath> 
#include "TextureLoader.h"
#include "Settings.h"

Circle::Circle(const Vector3& position, double radius, AnimationTextures textures, bool fillTexture, double animationDuration) :
	Animation(textures, animationDuration), pos(position), radius(radius), fillTexture(fillTexture)
{}

Circle::Circle(const Vector3& position, double radius, Color3ub color) :
	Animation(color), pos(position), radius(radius), fillTexture(true)
{}

Circle::~Circle(){}

void Circle::draw(void) const {
	// stretch texture to fit size
	// or use real world sizes and repeated texture
	GLfloat textureSize =
		fillTexture? 
		1 :
		(GLfloat)(2 * radius / Settings::TextureSizeMultiplier);

	// bottom
	int step = 360 / (int) Settings::CircleDrawPrecision;
	glBegin(GL_TRIANGLE_FAN);
	// center
	GLfloat center = (GLfloat)0.5 * textureSize;
	glTexCoord2f(center, center);
	glVertex3f((GLfloat) pos.x, (GLfloat) pos.y, centerHeight());
	for (int i = startAngle; i < endAngle; i+=step)
	{
		// points around center
		createVertex(i, textureSize);
	}
	// final point with endAngle
	createVertex(endAngle, textureSize);
	glEnd();
}

void Circle::createVertex(int angle, GLfloat textureSize) const {
	double degree = Vector3::deg2rad((double)angle);
	double dx = cos(degree);
	double dy = sin(degree);
	GLfloat x = (GLfloat)(dx / 2 + 0.5f) * textureSize;
	GLfloat y = (GLfloat)(dy / 2 + 0.5f) * textureSize;
	glTexCoord2f(x, y);
	glVertex3f((GLfloat)(pos.x + dx * radius), (GLfloat)(pos.y + dy * radius), circleHeight());
}
