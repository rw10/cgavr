#pragma once

#include <GL/glut.h>
#include <string>
#include <vector>


class Textures
{
public:
	~Textures();

	// singleton construction
	static Textures& get() {
		return INSTANCE[0];
	}

	static void init() {
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		INSTANCE.push_back(Textures());
		// enable 2d textures
	}


	GLuint wallTexture;
	GLuint groundTexture;

private:
	static std::vector<Textures> INSTANCE;

	Textures();

	bool readTextureFile(const std::string& file, GLuint& texture);

};
