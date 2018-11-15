#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	// init camera settings
	position = Vector3(3.0, -10.0, 80.0);
	lookAtPoint = Vector3(0.0, 0.0, 0.0);
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



void Camera::rotateAroundX(double degrees) {
	Vector3 delta = position - lookAtPoint;
	delta.rotateAroundX(degrees);
	position = lookAtPoint + delta;
	update();
}

void Camera::rotateAroundY(double degrees) {
	Vector3 delta = position - lookAtPoint;
	delta.rotateAroundY(degrees);
	position = lookAtPoint + delta;
	update();
}

void Camera::rotateAroundZ(double degrees) {
	Vector3 delta = position - lookAtPoint;
	delta.rotateAroundZ(degrees);
	position = lookAtPoint + delta; 
	update();
}


void Camera::move(double distance, double degrees) {
	Vector3 delta = lookAtPoint - position;
	// move only in xy-area
	delta._z = 0;
	delta.normalize(distance);
	delta.rotateAroundZ(90);
	position = position + delta;
	update();
}

void Camera::moveUp(double distance) {
	position._z += distance;
	update();
}
