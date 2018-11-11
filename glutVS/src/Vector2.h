#pragma once

#include "Vector3.h"

class Vector2 : public Vector3
{
public:
	Vector2() : Vector3() {}
	Vector2(double x, double y) : Vector3(x, y, 0){}
	~Vector2(){}

	// a vector3 will be flattened on the z value
	Vector2 operator=(const Vector3& vector3) const
	{
		return Vector2(
			vector3._x, vector3._y
		);
	}
};

