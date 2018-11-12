#include "pch.h"
#include "GL/glut.h"

#include <math.h>

#include "Wall.h"

Wall::Wall(const Vector2 begin, const Vector2 end, double width, const Color color) : begin(begin), end(end), width(width), color(color), cornerPoints(begin, end, width)
{
}

Wall::Wall() : begin(Vector2(0, 0)), end(0, 0), width(0), color(0, 0, 0), cornerPoints(begin, end, width)
{
}

Wall::~Wall() {
}

void Wall::draw(void) {

	// z dimension
	double floor = 0;
	double ceiling = 30;	

	// TODO: normals dont fit anymore (only top/bottom)

	glBegin(GL_QUADS);
	// top
	glColor3ub(color.r, color.g, color.b);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(cornerPoints.p11.x(), cornerPoints.p11.y(), ceiling);
	glVertex3f(cornerPoints.p12.x(), cornerPoints.p12.y(), ceiling);
	glVertex3f(cornerPoints.p22.x(), cornerPoints.p22.y(), ceiling);
	glVertex3f(cornerPoints.p21.x(), cornerPoints.p21.y(), ceiling);

	// bottom
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(cornerPoints.p11.x(), cornerPoints.p11.y(), floor);
	glVertex3f(cornerPoints.p12.x(), cornerPoints.p12.y(), floor);
	glVertex3f(cornerPoints.p22.x(), cornerPoints.p22.y(), floor);
	glVertex3f(cornerPoints.p21.x(), cornerPoints.p21.y(), floor);

	// front
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(cornerPoints.p11.x(), cornerPoints.p11.y(), floor);
	glVertex3f(cornerPoints.p11.x(), cornerPoints.p11.y(), ceiling);
	glVertex3f(cornerPoints.p12.x(), cornerPoints.p12.y(), ceiling);
	glVertex3f(cornerPoints.p12.x(), cornerPoints.p12.y(), floor);

	// back
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(cornerPoints.p21.x(), cornerPoints.p21.y(), floor);
	glVertex3f(cornerPoints.p21.x(), cornerPoints.p21.y(), ceiling);
	glVertex3f(cornerPoints.p22.x(), cornerPoints.p22.y(), ceiling);
	glVertex3f(cornerPoints.p22.x(), cornerPoints.p22.y(), floor);

	// right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(cornerPoints.p11.x(), cornerPoints.p11.y(), floor);
	glVertex3f(cornerPoints.p11.x(), cornerPoints.p11.y(), ceiling);
	glVertex3f(cornerPoints.p21.x(), cornerPoints.p21.y(), ceiling);
	glVertex3f(cornerPoints.p21.x(), cornerPoints.p21.y(), floor);

	// left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(cornerPoints.p12.x(), cornerPoints.p12.y(), floor);
	glVertex3f(cornerPoints.p12.x(), cornerPoints.p12.y(), ceiling);
	glVertex3f(cornerPoints.p22.x(), cornerPoints.p22.y(), ceiling);
	glVertex3f(cornerPoints.p22.x(), cornerPoints.p22.y(), floor);
	glEnd();
}
