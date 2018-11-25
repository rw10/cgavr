#pragma once

#include "Animation.h"

#include "Quad.h"
#include "Vector2.h"
#include "Color3ub.h"
#include "Settings.h"

class Wall : public Animation
{
public:
	Wall();
	~Wall();

	Wall(const Vector2& begin, const Vector2& end, AnimationTextures textures, double animationDuration = 1000.0, double width = Settings::WallWidth) :
		Animation(textures, animationDuration), begin(begin), end(end), cornerPoints(begin, end, width), width(width)
	{}

	Wall(const Vector2& begin, const Vector2& end, Color3ub color, double width = 0) :
		Animation(color), begin(begin), end(end), cornerPoints(begin, end, width), width(width)
	{}

	double getLength() const {
		return (begin - end).getLength();
	}

	Vector2 begin;
	Vector2 end;

protected:
	virtual void draw(void) const;

private:
	double width;

	Quad cornerPoints;
};

