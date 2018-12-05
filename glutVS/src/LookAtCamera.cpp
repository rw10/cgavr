
#include "LookAtCamera.h"

LookAtCamera::LookAtCamera() : Camera()
{
	// init camera settings
	position = Vector3(3.0, -10.0, 80.0);
	lookAtPoint = Vector3(0.0, 0.0, 0.0);
	initPerspective();
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

void LookAtCamera::initPerspective() {
	// Setup the view.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		// field of view in degree
		30.0,
		// aspect ratio
		1.0,
		// Z near
		1.0,
		// Z far
		1000.0
	);
	glMatrixMode(GL_MODELVIEW);
}