#include "pch.h"

#include "Circle.h"

#include "GL/glut.h"
#include <cmath> 
#include "Textures.h"
#include "Settings.h"

Circle::Circle(const Vector3& position, double radius, GLuint texture) :
	pos(position), radius(radius), texture(texture), color(255, 255, 255)
{}

Circle::Circle(const Vector3& position, double radius, Color3ub color) :
	pos(position), radius(radius), texture(0), color(color)
{}

Circle::~Circle(){}

void Circle::draw(void) const {
	if (texture != 0) {
		// enable texture
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		// use repeat mode for wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else {
		glDisable(GL_TEXTURE_2D);
		glColor3ub(color.r, color.g, color.b);
	}

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