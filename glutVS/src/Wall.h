#pragma once

#include "Vector2.h"
#include "Quad.h"
#include "Color.h"
#include "Drawable.h"

class Wall : public Drawable
{
public:
	Wall();
	~Wall();

	// TODO: add textures
	Wall(const Vector2 begin, const Vector2 end, double width, const Color color);

	void draw(void);

	Color color;
	Vector2 begin;
	Vector2 end;
	double width;

	Quad cornerPoints;

	// TODO:
	//Vector3 getLowCorner();
	//Vector3 getHighCorner();
	//void rotate(double angle, Vector3 axis);

private:
};

