#include "pch.h"
#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera() : Camera()
{
	// init camera settings
	position = Vector3(1.0, 0.0, 2.0); 

	lookingDirection = Vector3(1.0, 1.0, 0.0);
	lookingDirection.normalize();
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::rotateAroundX(double degrees) {
	lookingDirection.rotateAroundX(degrees);
	update();
}

void FirstPersonCamera::rotateAroundY(double degrees) {
	lookingDirection.rotateAroundY(degrees);
	update();
}

void FirstPersonCamera::rotateAroundZ(double degrees) {
	lookingDirection.rotateAroundZ(degrees);
	update();
}

void FirstPersonCamera::update() {
	lookAtPoint = position + lookingDirection;
	Camera::update();
}

