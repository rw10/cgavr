#include "pch.h"
#include "GL/glut.h"

#include <math.h>

#include "Wall.h"

#include "Textures.h"

Wall::Wall(const Vector2 begin, const Vector2 end, const Color3ub color, double width) :
	begin(begin), end(end), color(color), cornerPoints(begin, end, width), texture(0), width(width)
{}

Wall::Wall(const Vector2 begin, const Vector2 end, const GLuint texture, double width) :
	begin(begin), end(end), texture(texture), color(0, 0, 0), cornerPoints(begin, end, width), width(width)
{}

Wall::Wall() : 
	begin(Vector2(0, 0)), end(0, 0), color(0, 0, 0), cornerPoints(begin, end, Settings::WallWidth), texture(0), width(Settings::WallWidth)
{}

Wall::~Wall() 
{}

void Wall::draw(void) {

	// z dimension
	GLfloat floor = 0;
	GLfloat ceiling = (GLfloat) Settings::WallHeight;

	// TODO: normals dont fit anymore (only top/bottom)

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

	glBegin(GL_QUADS);
	
	// if no width, only show the sides
	if (width > 0) {

		// top
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), ceiling);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), ceiling);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), ceiling);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), ceiling);

		// bottom
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), floor);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), floor);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(cornerPoints.p22.gl_x(), cornerPoints.p22.gl_y(), floor);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), floor);

		// front
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), floor);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), ceiling);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), ceiling);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(cornerPoints.p12.gl_x(), cornerPoints.p12.gl_y(), floor);

		// back
		glNormal3f(0.0f, 1.0f, 0.0f);
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
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), floor);
	glTexCoord2f(0.0f, textureSizeY);
	glVertex3f(cornerPoints.p11.gl_x(), cornerPoints.p11.gl_y(), ceiling);
	glTexCoord2f(textureSizeX, textureSizeY);
	glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), ceiling);
	glTexCoord2f(textureSizeX, 0.0f);
	glVertex3f(cornerPoints.p21.gl_x(), cornerPoints.p21.gl_y(), floor);

	// left
	glNormal3f(-1.0f, 0.0f, 0.0f);
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
