#include "pch.h"

#include <GL/glut.h>
#include "GlutWindow.h"

#include "Constants.h"

#include "Histogram3D.h"
#include "Labyrinth.h"

#include "FirstPersonCamera.h"
#include "LookAtCamera.h"


GlutWindow* GlutWindow::INSTANCE = 0;

GlutWindow::GlutWindow()
{
	camera = std::shared_ptr<Camera>(new FirstPersonCamera());

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 100);
	glutCreateWindow(Constants::ProjectName.data());
	initialize();
}


GlutWindow::~GlutWindow()
{}

void GlutWindow::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& drawable : drawables) {
		drawable->draw();
	}

	// show axis
	for (auto& drawable : axis) {
		drawable.draw();
	}

	// in double buffering, this needs to be called to switch toggle between the shown and hidden buffer
	glutSwapBuffers();

	// flush to apply
	glFlush();
}

void GlutWindow::idleFunc() {

	// keyboard actions
	// for standard keys
	for (auto key = 0; key < keys.size(); key++) {
		if (keys[key]) {
			switch (key) {
			// WASD - control camera movement
			case 'w':
				camera->move(1, 0);
				break;
			case 's':
				camera->move(-1, 0);
				break;

			// strafe - movement
			case 'a':		// left
				camera->move(1, 90);
				break;
			case 'd':		// right
				camera->move(1, -90);
				break;
			default:
				break;
			}
		}
	}
	// for special keys (like the arrow keys)
	for (auto key = 0; key < specialkeys.size(); key++) {
		if (specialkeys[key]) {
			switch (key) {
				// control camera height
			case GLUT_KEY_UP:
				camera->moveUp(1);
				break;
			case GLUT_KEY_DOWN:
				camera->moveUp(-1);
				break;

				// control camera rotation
			case GLUT_KEY_LEFT:
				camera->rotateAroundZ(1);
				break;
			case GLUT_KEY_RIGHT:
				camera->rotateAroundZ(-1);
				break;
			default:
				break;
			}
		}
	}
}

void GlutWindow::keyboardFunc(unsigned char key, int , int ) {
	if (keys[key]) {
		//std::cout << "key '" << key << "' is already pressed" << std::endl;
	}
	else {
		// set the flag for the touched key
		keys[key] = true;

		std::cout << "key '" << key << "' pressed" << std::endl;
	}
}
void GlutWindow::keyboardUpFunc(unsigned char key, int , int ) {
	// unset the flag for the touched key
	keys[key] = false;

	std::cout << "key '" << key << "' released" << std::endl;
}


void GlutWindow::specialFunc(unsigned char key, int, int) {
	if (specialkeys[key]) {
		//std::cout << "key '" << key << "' is already pressed" << std::endl;
	}
	else {
		// set the flag for the touched key
		specialkeys[key] = true;

		std::cout << "specialkey '" << key << "' pressed" << std::endl;
	}
}
void GlutWindow::specialUpFunc(unsigned char key, int, int) {
	// unset the flag for the touched key
	specialkeys[key] = false;

	std::cout << "specialkey '" << key << "' released" << std::endl;
}


void GlutWindow::mouseFunc(int button, int state, int , int ) {
	// toggle the flag for the touched key

}

void GlutWindow::initialize(void)
{
	keys = std::vector<bool>(256, false);
	specialkeys = std::vector<bool>(256, false);

	// set the clear color
	glClearColor(0.0, 0.1, 0.5, 1);

	// Enable a single OpenGL light.
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);

	// Use depth buffering for hidden surface elimination.
	glEnable(GL_DEPTH_TEST);

	// enable 2d textures
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

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

	// show axis
	createAxis();

	// add labyrinth
	std::shared_ptr<Labyrinth> lab(new Labyrinth);
	double width = 0;
	for (int i = 0; i < 10; i++) {
		Wall wall(
			Vector2(i*10, 5*(i%3)),
			Vector2(i*10+20, 50+ 5*(i%3)),
			Color(125, 10, 23)
			//, 0				//width
		);
		lab->addWall(wall);
	}
	drawables.push_back(lab);


	// 3D Histogram
	//std::shared_ptr<Histogram3D> hist(new Histogram3D);
	//drawables.push_back(hist);
	
	// Adjust cube position to be asthetic angle.
	//glRotatef(60, 1.0, 0.0, 0.0);
	//glRotatef(-20, 0.0, 0.0, 1.0);

	// show both sides of objects
	//glDisable(GL_CULL_FACE);

	// define which side to show
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	//glEnable(GL_CLIP_DISTANCE0);

	camera->update();
}

void GlutWindow::createAxis() {
	double axisWidth = 1;

	// x axis
	axis.push_back(
		Block::createByCorners(
			Vector3(0, 0, 0),
			Vector3(100, axisWidth, axisWidth),
			Color(255, 0, 0)
		)
	);

	// y axis
	axis.push_back(
		Block::createByCorners(
			Vector3(0, 0, 0),
			Vector3(axisWidth, 100, axisWidth),
			Color(0, 255, 0)
		)
	);

	// z axis
	axis.push_back(
		Block::createByCorners(
			Vector3(0, 0, 0),
			Vector3(axisWidth, axisWidth, 100),
			Color(0, 0, 255)
		)
	);
}