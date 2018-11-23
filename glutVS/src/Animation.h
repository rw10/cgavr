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
	Animation(AnimationTextures animationTextures, double duration = 1000.0);
	Animation(Color3ub color);
	~Animation();

	// paint() can be overwritten:
	// if taking over texture handling manually
	// or if only calling children
	virtual void paint(double time);

protected:
	AnimationTextures textures;
	Color3ub color;
	size_t index;

	double singleTextureDuration;
	double elapsedTime;
};