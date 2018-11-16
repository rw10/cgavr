#include "pch.h"
#include "GL/glut.h"

#include <math.h>

#include "Wall.h"

#include "Constants.h"

Wall::Wall(const Vector2 begin, const Vector2 end, const Color color, double width) : begin(begin), end(end), width(width), color(color), cornerPoints(begin, end, width)
{
}

Wall::Wall() : begin(Vector2(0, 0)), end(0, 0), width(0), color(0, 0, 0), cornerPoints(begin, end, width)
{
}

Wall::~Wall() {
}

void Wall::draw(void) {

	// z dimension
	GLfloat floor = 0;
	GLfloat ceiling = Constants::WallHeight;

	// TODO: normals dont fit anymore (only top/bottom)

	glBegin(GL_QUADS);
	glColor3ub(color.r, color.g, color.b);
	
	// if no width, only show the sides
	if (width > 0) {

		// top
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), ceiling);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), ceiling);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), ceiling);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), ceiling);

		// bottom
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), floor);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), floor);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), floor);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), floor);

		// front
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), floor);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), ceiling);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), ceiling);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), floor);

		// back
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), floor);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), ceiling);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), ceiling);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), floor);

	}

	// right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), floor);
	glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), ceiling);
	glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), ceiling);
	glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), floor);

	// left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), floor);
	glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), ceiling);
	glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), ceiling);
	glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), floor);

	glEnd();
}
