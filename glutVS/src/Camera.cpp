#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	upDirection = Vector3(0.0, 0.0, 1.0);		// up is in positive Z direction
}

Camera::~Camera()
{
}

void Camera::update() {
	// load identity matrix as gluLookAt multiplies with previous matrices
	glLoadIdentity();

	// update the camera settings
	gluLookAt(
		position._x, position._y, position._z,  				// eye
		lookAtPoint._x, lookAtPoint._y, lookAtPoint._z,			// center
		upDirection._x, upDirection._y, upDirection._z			// up
	);

	// trigger repaint on next turn
	glutPostRedisplay();
}

void Camera::move(double distance, double degrees) {
	Vector3 delta = lookAtPoint - position;
	// move only in xy-area
	delta._z = 0;
	delta.normalize(distance);
	delta.rotateAroundZ(degrees);
	position = position + delta;
	update();
}

void Camera::moveUp(double distance) {
	position._z += distance;
	update();
}
