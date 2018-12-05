
#include "GL/glut.h"

#include <cmath> 

#include "Block.h"


Block Block::createByCorners(const Vector3& corner1, const Vector3& corner2, const Color3ub& color){
	Vector3 center(
		(corner1.x + corner2.x) / 2.0,
		(corner1.y + corner2.y) / 2.0,
		(corner1.z + corner2.z) / 2.0
	);
	Vector3 size(
		fabs(corner1.x - corner2.x),
		fabs(corner1.y + corner2.y),
		fabs(corner1.z + corner2.z)
	);

	return Block(center, size, color);
}

Block Block::createByCorners(const Vector3& corner1, const Vector3& corner2, AnimationTextures textures, double animationDuration) {
	Vector3 center(
		(corner1.x + corner2.x) / 2.0,
		(corner1.y + corner2.y) / 2.0,
		(corner1.z + corner2.z) / 2.0
	);
	Vector3 size(
		fabs(corner1.x - corner2.x),
		fabs(corner1.y + corner2.y),
		fabs(corner1.z + corner2.z)
	);

	return Block(center, size, textures, animationDuration);
}

Block Block::createByCenterSize(const Vector3& center, const Vector3& size, const Color3ub& color){
	return Block(center, size, color);
}

Block Block::createByCenterSize(const Vector3& center, const Vector3& size, AnimationTextures textures, double animationDuration) {
	return Block(center, size, textures, animationDuration);
}


Block::Block(const Vector3 center, const Vector3 size, const Color3ub color) : 
	Animation(color), pos(center), size(size)
{}

Block::Block(const Vector3 center, const Vector3 size, AnimationTextures textures, double animationDuration) :
	Animation(textures, animationDuration), pos(center), size(size)
{}

Block::Block() : Animation(Color3ub(0,0,0)), pos(Vector3(0, 0, 0)), size(0, 0, 0)
{}

Block::~Block(){
}


void Block::draw(void) const {

	double deltaX = size.x / 2;
	double deltaY = size.y / 2;
	double deltaZ = size.z / 2;

	// calc corner points
	Vector3 low(pos.x - deltaX, pos.y - deltaY, pos.z - deltaZ);
	Vector3 high(pos.x + deltaX, pos.y + deltaY, pos.z + deltaZ);

	// save color status
	//glPushAttrib(GL_CURRENT_BIT);

	glBegin(GL_QUADS);
	// top
	glColor3ub(color.r, color.g, color.b);
	glVertex3f(low.gl_x(), low.gl_y(), high.gl_z());
	glVertex3f(high.gl_x(), low.gl_y(), high.gl_z());
	glVertex3f(high.gl_x(), high.gl_y(), high.gl_z());
	glVertex3f(low.gl_x(), high.gl_y(), high.gl_z());

	// bottom
	glVertex3f(low.gl_x(), low.gl_y(), low.gl_z());
	glVertex3f(high.gl_x(), low.gl_y(), low.gl_z());
	glVertex3f(high.gl_x(), high.gl_y(), low.gl_z());
	glVertex3f(low.gl_x(), high.gl_y(), low.gl_z());

	// front
	glVertex3f(high.gl_x(), low.gl_y(), low.gl_z());
	glVertex3f(high.gl_x(), low.gl_y(), high.gl_z());
	glVertex3f(low.gl_x(), low.gl_y(), high.gl_z());
	glVertex3f(low.gl_x(), low.gl_y(), low.gl_z());

	// back
	glVertex3f(low.gl_x(), high.gl_y(), low.gl_z());
	glVertex3f(low.gl_x(), high.gl_y(), high.gl_z());
	glVertex3f(high.gl_x(), high.gl_y(), high.gl_z());
	glVertex3f(high.gl_x(), high.gl_y(), low.gl_z());

	// right
	glVertex3f(high.gl_x(), high.gl_y(), low.gl_z());
	glVertex3f(high.gl_x(), high.gl_y(), high.gl_z());
	glVertex3f(high.gl_x(), low.gl_y(), high.gl_z());
	glVertex3f(high.gl_x(), low.gl_y(), low.gl_z());

	// left
	glVertex3f(low.gl_x(), high.gl_y(), low.gl_z());
	glVertex3f(low.gl_x(), high.gl_y(), high.gl_z());
	glVertex3f(low.gl_x(), low.gl_y(), high.gl_z());
	glVertex3f(low.gl_x(), low.gl_y(), low.gl_z());
	glEnd();

	// restore color status
	//glPopAttrib();
}
