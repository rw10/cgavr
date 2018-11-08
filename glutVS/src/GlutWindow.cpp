#include "pch.h"

#include <GL/glut.h>
#include "GlutWindow.h"

#include "Histogram3D.h"


GlutWindow* GlutWindow::INSTANCE = 0;

GlutWindow::GlutWindow()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 100);
	glutCreateWindow("3D Histogram");
	initialize();
}


GlutWindow::~GlutWindow()
{
}

void GlutWindow::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& drawable : drawables) {
		drawable->draw();
	}

	glutSwapBuffers();


	/*
	rotation = (rotation + 1) % 180;

	if (rotation < 45 || rotation >= 135) {
		glRotatef(4.0f, 0.0f, 1.0f, 0.0f);
	}
	else {
		glRotatef(-4.0f, 0.0f, 1.0f, 0.0f);
	}
	*/


	glFlush();


	// force repaint
	//glutPostRedisplay();
}

void GlutWindow::idleFunc() {
	for (auto key = 0; key < keys.size(); key++) {
		if (keys[key]) {
			switch (key) {
			case 'w':
				//cameraPos[2]++;
				break;
			case 'a':
				//cameraPos[0]++;
				break;
			case 's':
				//cameraPos[2]--;
				break;
			case 'd':
				//cameraPos[0]--;
				break;
			default:
				break;
			}
		}
	}


}

void GlutWindow::keyboardFunc(unsigned char key, int x, int y) {
	// toggle the flag for the touched key
	keys[key] = !keys[key];
}


void GlutWindow::mouseFunc(int button, int state, int x, int y) {
	// toggle the flag for the touched key

}

void GlutWindow::initialize(void)
{
	keys = std::vector<bool>(256, false);
	cameraPos = Vector3(0.0, 30.0, 80.0);
	cameraLookAt = Vector3(0.0, 0.0, 0.0);
	cameraUp = Vector3(0.0, 0.0, 1.0);		// up is in positive Z direction

	// Enable a single OpenGL light.
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);

	// Use depth buffering for hidden surface elimination.
	glEnable(GL_DEPTH_TEST);

	// Setup the view.
	glMatrixMode(GL_PROJECTION);
	gluPerspective(
		// field of view in degree
		40.0,
		// aspect ratio
		1.0,
		// Z near
		1.0,
		// Z far
		1000.0
	);
	glMatrixMode(GL_MODELVIEW);

	gluLookAt(
		cameraPos._x, cameraPos._y, cameraPos._z,  				// eye
		cameraLookAt._x, cameraLookAt._y, cameraLookAt._z,		// center
		cameraUp._x, cameraUp._y, cameraUp._z					// up
	);

	glClearColor(0.0, 0.1, 0.4, 1);

	// Adjust cube position to be asthetic angle.
	//glRotatef(60, 1.0, 0.0, 0.0);
	//glRotatef(-20, 0.0, 0.0, 1.0);



	// show both sides of objects
	//glDisable(GL_CULL_FACE);

	// define which side to show
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	//glEnable(GL_CLIP_DISTANCE0);

	std::shared_ptr<Histogram3D> hist (new Histogram3D);
	drawables.push_back(hist);
}