#pragma once

#include "Drawable.h"

#include "Quad.h"
#include "Vector2.h"
#include "Color3ub.h"
#include "Settings.h"

class Wall : public Drawable
{
public:
	Wall();
	~Wall();

	// TODO: add textures
	Wall(const Vector2 begin, const Vector2 end, const Color3ub color, double width = 0);
	Wall(const Vector2 begin, const Vector2 end, const GLuint texture, double width = Settings::WallWidth);

	double getLength() const {
		return (begin - end).getLength();
	}

	void draw(void) const;

	Color3ub color;
	Vector2 begin;
	Vector2 end;
	GLuint texture;
	double width;

	Quad cornerPoints;

	// TODO:
	//Vector3 getLowCorner();
	//Vector3 getHighCorner();
	//void rotate(double angle, Vector3 axis);

private:
};

