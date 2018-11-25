#pragma once

#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera();
	~FirstPersonCamera();

	virtual void update();

	virtual void rotateAroundX(double degrees);
	virtual void rotateAroundY(double degrees);
	virtual void rotateAroundZ(double degrees);

protected:
	Vector3 lookingDirection;
	virtual void initPerspective();

};