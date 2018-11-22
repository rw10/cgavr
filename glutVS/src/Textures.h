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
		return INSTANCES[0];
	}

	static void init() {
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		INSTANCES.push_back(Textures());
		// enable 2d textures
	}


	GLuint wallTexture;
	GLuint groundTexture;

private:
	static std::vector<Textures> INSTANCES;

	Textures();

	bool readTextureFile(const std::string& file, GLuint& texture);

};
