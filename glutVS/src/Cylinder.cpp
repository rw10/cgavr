#include "pch.h"

#include "Cylinder.h"

#include "GL/glut.h"
#include "Textures.h"
#include "Settings.h"
#include "Constants.h"

#include <cmath>

Cylinder::Cylinder(const Vector3& position, double radius, double height, GLuint texture) :
	pos(position), radius(radius), height(height), texture(texture), color(255, 255, 255)
{
	floorCircle = new Circle(pos, radius, texture);

	Vector3 cPos = pos;
	cPos.z += height;
	ceilingCircle = new Circle(cPos, radius, texture);
}

Cylinder::Cylinder(const Vector3& position, double radius, double height, Color3ub color) :
	pos(position), radius(radius), height(height), texture(0), color(color)
{
	floorCircle = new Circle(pos, radius, color);

	Vector3 cPos = pos;
	cPos.z += height;
	ceilingCircle = new Circle(cPos, radius, color);
}

Cylinder::~Cylinder() {
	delete floorCircle;
	delete ceilingCircle;
}

void Cylinder::draw(void) {

	// top and bottom
	floorCircle->draw();
	ceilingCircle->draw();


	// --- draw the side ---


	// z dimension
	GLfloat floor = (GLfloat)pos.z;
	GLfloat ceiling = (GLfloat)(floor + height);

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