#pragma once

#include "Vector3.h"

class Camera
{
public:
	Camera();
	~Camera();

	Vector3 position;
	Vector3 lookAtPoint;
	Vector3 upDirection;

	void rotateAroundX(double degrees);
	void rotateAroundY(double degrees);
	void rotateAroundZ(double degrees);

	void update();

private:

};

