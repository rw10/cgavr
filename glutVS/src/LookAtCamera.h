#pragma once

#include "Camera.h"

class LookAtCamera : public Camera
{
public:
	LookAtCamera();
	~LookAtCamera();

	virtual void rotateAroundX(double degrees);
	virtual void rotateAroundY(double degrees);
	virtual void rotateAroundZ(double degrees);

protected:
	virtual void initPerspective();

};

