#pragma once

#include <GL/glut.h>
#include <string>
#include <vector>
#include <mutex>
#include "Types.h"


class TextureLoader
{
public:
	~TextureLoader();

	// singleton construction
	static TextureLoader& get() {
		return INSTANCES[0];
	}

	static void init() {
		loadMutex.lock();
		// enable 2d textures
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		INSTANCES.push_back(TextureLoader());
		loadMutex.unlock();
	}

	AnimationTextures wallTexture;
	AnimationTextures groundTexture;
	AnimationTextures playerTexture;
	AnimationTextures arrowTexture;

private:
	static std::vector<TextureLoader> INSTANCES;
	static std::mutex loadMutex;

	TextureLoader();

	bool readTextureFile(const std::string& file, GLuint& texture);
	bool readTextureFile(const std::string& file, AnimationTextures& animation);
	bool readTextureFiles(const std::vector<std::string>& files, AnimationTextures& textures);

};
