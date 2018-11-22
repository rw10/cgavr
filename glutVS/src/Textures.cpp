
#include "pch.h"

#include "Textures.h"

#include <iostream>
#include <SOIL.h>


std::vector<Textures> Textures::INSTANCE = std::vector<Textures>();

Textures::Textures()
{
	readTextureFile("img/wall.png", wallTexture);
	readTextureFile("img/ground2.jpg", groundTexture);
}

Textures::~Textures()
{
}

bool Textures::readTextureFile(const std::string& file, GLuint& texture) {
	//std::string file = "img/wall.png";

	/* load an image file directly as a new OpenGL texture */
	texture = SOIL_load_OGL_texture
	(
		file.data(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		//SOIL_FLAG_INVERT_Y
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	if (texture == 0) {
		std::cout << "error reading file: " << file.data() << std::endl;
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}
