#include "pch.h"

#include "Animation.h"

Animation::Animation(AnimationTextures animationTextures, double duration) :
	textures(animationTextures), color(255,255,255)
{
	index = 0;
	singleTextureDuration = duration / animationTextures.size();
	elapsedTime = 0;
}

Animation::Animation(Color3ub color) : color(color)
{
	index = 0;
	singleTextureDuration = 0;
	elapsedTime = 0;
}

Animation::~Animation() {}

void Animation::paint(double time) {

	// enable texture
	if (textures.size() != 0) {
		// TODO: toggling every repaint is much too fast!!!!!

		if (textures.size() != 1) {
			elapsedTime += time;
			if (elapsedTime >= singleTextureDuration) {
				elapsedTime -= singleTextureDuration;
				// toggle used texture
				index++;
				index %= textures.size();
			}
		}

		// enable texture
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[index]);
		// use repeat mode for wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else {
		glDisable(GL_TEXTURE_2D);
		glColor3ub(color.r, color.g, color.b);
	}

	draw();
}