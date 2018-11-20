#pragma once

#include <GL/glut.h>
#include <string>


class Textures
{
public:

	// singleton construction
	static Textures& get() {
		static Textures INSTANCE;
		return INSTANCE;
	}


	GLuint wallTexture;
	GLuint groundTexture;

private:

	Textures();
	~Textures();

	bool readTextureFile(const std::string& file, GLuint& texture);

};
