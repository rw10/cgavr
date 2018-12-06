


#include "TextureLoader.h"

#include <iostream>
#include <SOIL.h>


std::vector<TextureLoader> TextureLoader::INSTANCES = std::vector<TextureLoader>();
std::mutex TextureLoader::loadMutex;

TextureLoader::TextureLoader()
{
	readTextureFile("img/wall.png", wallTexture);
	readTextureFile("img/arrow.png", arrowTexture);
	readTextureFile("img/ground2.jpg", groundTexture);

	std::vector<std::string> imgs;
	imgs.push_back("img/wall.png");
	imgs.push_back("img/ground.jpg");
	imgs.push_back("img/ground2.jpg");
	imgs.push_back("img/grass.png");
	imgs.push_back("img/rockwall.jpg");
	imgs.push_back("img/wall.jpg");
	readTextureFiles(imgs, playerTexture);
}

TextureLoader::~TextureLoader()
{
}

bool TextureLoader::readTextureFiles(const std::vector<std::string>& files, AnimationTextures& animation) {
	bool anysuccess = false;

	for (auto file : files) {
		GLuint gluIndex = 0;
		bool success = readTextureFile(file, gluIndex);
		if (success) {
			animation.push_back(gluIndex);
		}

		// a single successfully loaded texture will result in a success return value
		anysuccess |= success;
	}

	return anysuccess;
}

bool TextureLoader::readTextureFile(const std::string& file, AnimationTextures& animation) {
	GLuint gluIndex = 0;
	bool success = readTextureFile(file, gluIndex);
	if (success) {
		animation.push_back(gluIndex);
	}
	return success;
}

bool TextureLoader::readTextureFile(const std::string& file, GLuint& texture) {
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
