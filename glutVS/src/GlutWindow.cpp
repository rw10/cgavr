#include "pch.h"

#include "GlutWindow.h"

#include <GL/glut.h>
#include <iostream>

#include "Settings.h"
#include "ViewSettings.h"
#include "Dijkstra.h"

// drawables
#include "Model.h"

// surfaces
#include "Color3f.h"
#include "TextureLoader.h"

// cameras
#include "FirstPersonCamera.h"
#include "LookAtCamera.h"
#include "TopDownCamera.h"
#include "PlayerViewCamera.h"

std::vector<GlutWindow> GlutWindow::INSTANCES = std::vector<GlutWindow>();
int GlutWindow::activeWindow = 0;


GlutWindow::GlutWindow(size_t index) : windowType((WindowType)(index))
{
	// create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0 + (int)index * 800, 100);
	glutCreateWindow(Settings::ProjectName.data());

	// load textures
	TextureLoader::init();

	// init window settings
	initialize();
}


GlutWindow::~GlutWindow()
{}

double clockToMilliseconds(clock_t ticks) {
	return (ticks / double(CLOCKS_PER_SEC)) * 1000.0;
}

void GlutWindow::display() {
	camera->update();

	clock_t before = clock_ticks;
	clock_ticks = clock();
	double delta = clockToMilliseconds(clock_ticks - before);
	//double fps = 1000.0 / delta;
	//std::cout << "ms: "<< delta << "\t fps:" << fps << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const auto& drawables = Model::get().getDrawables();
	for (const auto& drawable : drawables) {
		drawable->show(delta, viewSettings);
	}

	// show axis
	axis.show(delta, viewSettings);

	// in double buffering, this needs to be called to switch toggle between the shown and hidden buffer
	glutSwapBuffers();

	// flush to apply
	glFlush();
}

void GlutWindow::idleFunc() {

	// keyboard actions
	// for standard keys
	for (const auto& key : keys) {
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
		case '+':
			Settings::PlayerSpeed *= 1.01;
			break;
		case '-':
			Settings::PlayerSpeed /= 1.01;
			break;
		default:
			break;
		}
	}
	// for special keys (like the arrow keys)
	for (const auto& key : specialkeys) {
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

	Model::get().update();
}

void GlutWindow::keyboardFunc(unsigned char key, int , int ) {
	if (keys.count(key) != 0) {
		//std::cout << "key '" << key << "' is already pressed" << std::endl;
	}
	else {
		// set the flag for the touched key -> action during idleFunc
		keys.insert(key);

		std::cout << "key '" << key << "' pressed" << std::endl;
	}
}
void GlutWindow::keyboardUpFunc(unsigned char key, int , int ) {
	// unset the flag for the touched key -> action during idleFunc
	keys.erase(key);

	// direct action
	switch (key) {
	case '1':
		viewSettings.wayPointWalls.show = !viewSettings.wayPointWalls.show;
		break;
	case '2':
		viewSettings.autoRouteWalls.show = !viewSettings.autoRouteWalls.show;
		break;
	case '3':
		viewSettings.lvl1RouteWalls.show = !viewSettings.lvl1RouteWalls.show;
		break;
	case '4':
		viewSettings.lvl1DeniedRouteWalls.show = !viewSettings.lvl1DeniedRouteWalls.show;
		break;
	case '5':
		viewSettings.lvl2RouteWalls.show = !viewSettings.lvl2RouteWalls.show;
		break;
	case '6':
		viewSettings.lvl2DeniedRouteWalls.show = !viewSettings.lvl2DeniedRouteWalls.show;
		break;
	case '7':
		viewSettings.additionalRouteWalls.show = !viewSettings.additionalRouteWalls.show;
		break;
	case '8':
		viewSettings.additionalDeniedRouteWalls.show = !viewSettings.additionalDeniedRouteWalls.show;
		break;
	case '9':
		viewSettings.dijkstraRoute.show = !viewSettings.dijkstraRoute.show;
		break;
	case '0':
		viewSettings.ShowAxis = !viewSettings.ShowAxis;
		break;
	default:
		break;
	}

	// trigger redisplay
	glutPostRedisplay();

	std::cout << "key '" << key << "' released" << std::endl;
}


void GlutWindow::specialFunc(unsigned char key, int, int) {
	if (specialkeys.count(key) != 0) {
		//std::cout << "key '" << key << "' is already pressed" << std::endl;
	}
	else {
		// set the flag for the touched key
		specialkeys.insert(key);

		std::cout << "specialkey '" << key << "' pressed" << std::endl;
	}
}
void GlutWindow::specialUpFunc(unsigned char key, int, int) {
	// unset the flag for the touched key
	specialkeys.erase(key);

	std::cout << "specialkey '" << key << "' released" << std::endl;
}


void GlutWindow::mouseFunc(int , int , int , int ) {
	// toggle the flag for the touched key

}

void GlutWindow::initialize(void)
{
	// set the clear color
	// glClearColor(0.0f, 0.1f, 0.5f, 1.0f);	// some dark blue
	glClearColor(0.22f, 0.69f, 0.87f, 1.0f);	//SummerSky

	// Use depth buffering for hidden surface elimination.
	glEnable(GL_DEPTH_TEST);
	
	// Enable a single OpenGL light.
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);

	// show both sides of objects
	//glDisable(GL_CULL_FACE);

	// define which side to show
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	//glEnable(GL_CLIP_DISTANCE0);


	// window title
	windowTitle = Settings::ProjectName + ": ";
	switch (windowType) {
	case WindowType::PLAYERVIEW:
		windowTitle += "Player View";
		camera = std::shared_ptr<Camera>(new PlayerViewCamera());
		break;
	case WindowType::TOPDOWN:
		windowTitle += "Top-Down View";
		camera = std::shared_ptr<Camera>(new TopDownCamera());
		break;
	default:
		windowTitle += "undefined";
		break;
	}
	glutSetWindowTitle(windowTitle.data());

	clock_ticks = clock();
}