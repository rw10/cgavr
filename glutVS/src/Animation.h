#pragma once

#include "Drawable.h"
#include "Types.h"
#include "Color3ub.h"

class Animation : public Drawable {
public:
	/*
	* the list of textures is toggled in constant intervals by calling paint(delta_time)
	* the duration-parameter defines the overall lenght of the animation in milliseconds
	*/
	Animation(AnimationTextures animationTextures, double duration);
	Animation(Color3ub color);
	~Animation();

	// animate() can be overwritten:
	// if taking over texture handling manually
	// or if only calling children
	virtual void animate(const double time);

	void setAnimationTextures(AnimationTextures animationTextures) {
		textures = animationTextures;
	}

	void setColor(Color3ub objectColor) {
		color = objectColor;
	}

	Vector3 rotation;
	Vector3 rotationCenter;

protected:
	
	AnimationTextures textures;
	Color3ub color;
	size_t index;

	double singleTextureDuration;
	double elapsedTime;
};