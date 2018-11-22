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
		position.x, position.y, position.z,  				// eye
		lookAtPoint.x, lookAtPoint.y, lookAtPoint.z,		// center
		upDirection.x, upDirection.y, upDirection.z			// up
	);

	// trigger repaint on next turn

	glutPostRedisplay();
}

void Camera::move(double distance, double degrees) {
	Vector3 delta = lookAtPoint - position;
	// move only in xy-area
	delta.z = 0;
	delta.normalize(distance);
	delta.rotateAroundZ(degrees);
	position = position + delta;
	update();
}

void Camera::moveUp(double distance) {
	position.z += distance;
	update();
}

void Camera::moveToPoint3D(const Vector3& point) {
	moveEnvironment(point);
	this->position = point;
	update();
}

void Camera::moveToPoint2D(const Vector3& point) {
	moveEnvironment(point);
	this->position.x = point.x;
	this->position.y = point.y;
	update();
}
