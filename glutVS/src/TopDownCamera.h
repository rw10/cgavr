#pragma once

#include "LookAtCamera.h"

class TopDownCamera : public LookAtCamera
{
public:
	TopDownCamera();
	~TopDownCamera();

	virtual void move(double distance, double degrees);

protected:
	virtual void moveEnvironment(const Vector3& point);
};