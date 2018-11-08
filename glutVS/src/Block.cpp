#include "pch.h"
#include "GL/glut.h"

#include <math.h>

#include "Block.h"


Block Block::createByCorners(const Vector3& corner1, const Vector3& corner2, const Color& color){
	Vector3 center(
		(corner1._x + corner2._x) / 2.0,
		(corner1._y + corner2._y) / 2.0,
		(corner1._z + corner2._z) / 2.0
	);
	Vector3 size(
		fabs(corner1._x - corner2._x),
		fabs(corner1._y + corner2._y),
		fabs(corner1._z + corner2._z)
	);

	return Block(center, size, color);
}

Block Block::createByCenterSize(const Vector3& center, const Vector3& size, const Color& color){
	return Block(center, size, color);
}


Block::Block(const Vector3 center, const Vector3 size, const Color color) : pos(center), size(size), color(color)
{}

Block::Block() : pos(Vector3(0, 0, 0)), size(0, 0, 0), color(0, 0, 0)
{}

Block::~Block(){
}


void Block::draw(void) {

	double deltaX = size._x / 2;
	double deltaY = size._y / 2;
	double deltaZ = size._z / 2;

	// calc corner points
	Vector3 low(pos._x - deltaX, pos._y - deltaY, pos._z - deltaZ);
	Vector3 high(pos._x + deltaX, pos._y + deltaY, pos._z + deltaZ);

	glBegin(GL_QUADS);
	// top
	glColor3ub(color.r, color.g, color.b);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(low.x(), low.y(), high.z());
	glVertex3f(high.x(), low.y(), high.z());
	glVertex3f(high.x(), high.y(), high.z());
	glVertex3f(low.x(), high.y(), high.z());

	// bottom
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(low.x(), low.y(), low.z());
	glVertex3f(high.x(), low.y(), low.z());
	glVertex3f(high.x(), high.y(), low.z());
	glVertex3f(low.x(), high.y(), low.z());

	// front
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(high.x(), low.y(), low.z());
	glVertex3f(high.x(), low.y(), high.z());
	glVertex3f(low.x(), low.y(), high.z());
	glVertex3f(low.x(), low.y(), low.z());

	// back
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(low.x(), high.y(), low.z());
	glVertex3f(low.x(), high.y(), high.z());
	glVertex3f(high.x(), high.y(), high.z());
	glVertex3f(high.x(), high.y(), low.z());

	// right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(high.x(), high.y(), low.z());
	glVertex3f(high.x(), high.y(), high.z());
	glVertex3f(high.x(), low.y(), high.z());
	glVertex3f(high.x(), low.y(), low.z());

	// left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(low.x(), high.y(), low.z());
	glVertex3f(low.x(), high.y(), high.z());
	glVertex3f(low.x(), low.y(), high.z());
	glVertex3f(low.x(), low.y(), low.z());
	glEnd();
}
