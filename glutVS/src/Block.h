#pragma once

#include "Color3ub.h"
#include "Vector3.h"

#include "Drawable.h"

class Block : public Drawable
{
public:
	Block();
	~Block();

	// factories
	static Block createByCorners(const Vector3& corner1, const Vector3& corner2, const Color3ub& color);
	static Block createByCenterSize(const Vector3& center, const Vector3& size, const Color3ub& color);

	void draw(void);

	Color3ub color;
	Vector3 pos;
	Vector3 size;

private:
	Block(const Vector3 center, const Vector3 size, const Color3ub color);
};

