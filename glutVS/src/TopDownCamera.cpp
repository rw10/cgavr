
#include "TopDownCamera.h"

TopDownCamera::TopDownCamera() : LookAtCamera()
{
	// init camera settings
	Vector3 delta = Vector3(0.0, -0.1, 200.0);
	lookAtPoint = Vector3(50.0, 50.0, 0.0);
	position = lookAtPoint + delta;
}

TopDownCamera::~TopDownCamera()
{
}

void TopDownCamera::move(double distance, double degrees) {
	Vector3 delta = lookAtPoint - position;
	// move only in xy-area
	delta.z = 0;
	delta.normalize(distance);
	delta.rotateAroundZ(degrees);
	position = position + delta;
	lookAtPoint = lookAtPoint + delta;
	update();
}

void TopDownCamera::moveEnvironment(const Vector3& point) {
	// move the lookAt-Point along with the camera position, as we want a top-down-view

	Vector3 delta = point - position;
	// move focus point only in xy-area
	delta.z = 0;
	lookAtPoint = lookAtPoint + delta;
}