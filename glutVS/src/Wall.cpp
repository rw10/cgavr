
#include "GL/glut.h"

#include <cmath> 

#include "Wall.h"

#include "TextureLoader.h"


Wall::Wall() : 
	Animation(Color3ub(0,0,0)), begin(Vector2(0, 0)), end(0, 0), cornerPoints(begin, end, Settings::WallWidth), width(Settings::WallWidth)
{}

Wall::~Wall() 
{}

void Wall::draw(void) const {
	// z dimension
	GLfloat floor = 0;
	GLfloat ceiling = (GLfloat) Settings::WallHeight;

	// TODO: normals dont fit anymore (only top/bottom)
	
	glBegin(GL_QUADS);
	
	// if no width, only show the sides
	if (width > 0) {

		// top
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), ceiling);
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), ceiling);
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), ceiling);
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), ceiling);

		// bottom
		/*
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), floor);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), floor);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), floor);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), floor);
		*/

		// front
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), floor);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), ceiling);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), ceiling);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), floor);

		// back
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), floor);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), ceiling);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), ceiling);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), floor);

	}

	GLfloat textureSizeX = (GLfloat)((end - begin).getLength() / Settings::TextureSizeMultiplier);
	GLfloat textureSizeY = (GLfloat)((ceiling - floor) / Settings::TextureSizeMultiplier);

	// right
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), floor);
	glTexCoord2f(0.0f, textureSizeY);
	glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), ceiling);
	glTexCoord2f(textureSizeX, textureSizeY);
	glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), ceiling);
	glTexCoord2f(textureSizeX, 0.0f);
	glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), floor);

	// left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), floor);
	glTexCoord2f(0.0f, textureSizeY);
	glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), ceiling);
	glTexCoord2f(textureSizeX, textureSizeY);
	glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), ceiling);
	glTexCoord2f(textureSizeX, 0.0f);
	glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), floor);

	glEnd();
}
