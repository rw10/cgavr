#include "pch.h"

#include <GL/glut.h>
#include "GlutWindow.h"

#include "Settings.h"
#include "Dijkstra.h"

// drawables
#include "Histogram3D.h"
#include "LabyrinthBuilder.h"
#include "Cylinder.h"
#include "Cone.h"

// surfaces
#include "Color3f.h"
#include "Textures.h"

// cameras
#include "FirstPersonCamera.h"
#include "LookAtCamera.h"
#include "TopDownCamera.h"
#include "FollowPathCamera.h"

std::vector<GlutWindow> GlutWindow::INSTANCES = std::vector<GlutWindow>();
int GlutWindow::active = 0;

GlutWindow::GlutWindow(int index)
{
	this->index = index;

	camera = std::shared_ptr<Camera>(new FirstPersonCamera());
	camera = std::shared_ptr<Camera>(new LookAtCamera());
	camera = std::shared_ptr<Camera>(new TopDownCamera());

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 100);
	glutCreateWindow(Settings::ProjectName.data());

	Textures::init();

	initialize();
}


GlutWindow::~GlutWindow()
{}

void GlutWindow::display() {
	camera->update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& drawable : drawables) {
		drawable->draw();
	}

	// show axis
	axis.draw();

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

	camera->update();
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
		Settings::wayPointWalls.show = !Settings::wayPointWalls.show;
		break;
	case '2':
		Settings::autoRouteWalls.show = !Settings::autoRouteWalls.show;
		break;
	case '3':
		Settings::lvl1RouteWalls.show = !Settings::lvl1RouteWalls.show;
		break;
	case '4':
		Settings::lvl1DeniedRouteWalls.show = !Settings::lvl1DeniedRouteWalls.show;
		break;
	case '5':
		Settings::lvl2RouteWalls.show = !Settings::lvl2RouteWalls.show;
		break;
	case '6':
		Settings::lvl2DeniedRouteWalls.show = !Settings::lvl2DeniedRouteWalls.show;
		break;
	case '7':
		Settings::additionalRouteWalls.show = !Settings::additionalRouteWalls.show;
		break;
	case '8':
		Settings::additionalDeniedRouteWalls.show = !Settings::additionalDeniedRouteWalls.show;
		break;
	case '9':
		Settings::dijkstraRoute.show = !Settings::dijkstraRoute.show;
		break;
	case '0':
		Settings::ShowAxis = !Settings::ShowAxis;
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
	//keys = std::vector<bool>(256, false);
	//specialkeys = std::vector<bool>(256, false);

	// set the clear color
	// glClearColor(0.0f, 0.1f, 0.5f, 1.0f);	// some dark blue
	glClearColor(0.22f, 0.69f, 0.87f, 1.0f);				//SummerSky = color red 0.22 green 0.69 blue 0.87
	//glClearColor();				//NewMidnightBlue = color red 0.00 green 0.00 blue 0.61
	

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



		// add labyrinth
		std::shared_ptr<Labyrinth> lab = LabyrinthBuilder::build();
		drawables.push_back(lab);
		Dijkstra dijkstra = lab->calculateRoute(
			Vector2(45, 5),
			Vector2(95, 55)
		);

		// also use position of current cam as first part of the route
		// effect: fall into labyrinth
		// TODO: use point above start instead of camera-position
		std::vector<Vector2> route;
		route.reserve(1 + dijkstra.route.size()); // preallocate memory
		route.push_back(camera->getPosition());
		route.insert(route.end(), dijkstra.route.begin(), dijkstra.route.end());

	if (index == 2) {
		camera = std::shared_ptr<Camera>(new FollowPathCamera(route));
	}
	

	// 3D Objects
	//std::shared_ptr<ConeTop> c(new ConeTop(Vector3(0,0,0), 6, 30, Textures::get().wallTexture));
	//drawables.push_back(c);

	// 3D Histogram
	//std::shared_ptr<Histogram3D> hist(new Histogram3D);
	//drawables.push_back(hist);

	// show both sides of objects
	//glDisable(GL_CULL_FACE);

	// define which side to show
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	//glEnable(GL_CLIP_DISTANCE0);

	camera->update();
}