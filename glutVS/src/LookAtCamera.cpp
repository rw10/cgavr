#include "pch.h"
#include "LookAtCamera.h"

LookAtCamera::LookAtCamera() : Camera()
{
	// init camera settings
	position = Vector3(3.0, -10.0, 80.0);
	lookAtPoint = Vector3(0.0, 0.0, 0.0);
}

LookAtCamera::~LookAtCamera()
{
}

void LookAtCamera::rotateAroundX(double degrees) {
	Vector3 delta = position - lookAtPoint;
	delta.rotateAroundX(degrees);
	position = lookAtPoint + delta;
	update();
}

void LookAtCamera::rotateAroundY(double degrees) {
	Vector3 delta = position - lookAtPoint;
	delta.rotateAroundY(degrees);
	position = lookAtPoint + delta;
	update();
}

void LookAtCamera::rotateAroundZ(double degrees) {
	Vector3 delta = position - lookAtPoint;
	delta.rotateAroundZ(degrees);
	position = lookAtPoint + delta; 
	update();
}