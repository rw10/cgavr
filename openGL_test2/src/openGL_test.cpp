/*
 * openGL_test.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */


#include <opencv2/opencv.hpp>
#include <GL/glut.h>

#include <chrono>
#include <thread>

#include <vector>


cv::Mat loadImage( int argc, char** argv ){
	cv::Mat image;

	if(argc != 2){
		printf( "No image file specified \n" );
		return image;
	}
	image = cv::imread( argv[1], 1 );
	if(!image.data){
		printf( "No image data \n" );
		return image;
	}

	return image;
}

void viewImage(cv::Mat image){
	cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
	cv::imshow( "Display Image", image );
	cv::waitKey(0);
}

// bools for each key, init with all false
std::vector<bool> keys(256,false);

std::vector<float> cameraPos = {0.0f, 5.0f, 5.0f};

void createBlock(float x, float y, float height);

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	createBlock(0,0,1);
	glutSwapBuffers();


	//glRotatef(1.0f, 0.0f, 1.0f, 0.0f);

	glFlush();


	// force repaint
	glutPostRedisplay();
}

void createBlock(float x, float y, float height){

	glBegin(GL_QUADS);
	// top
	glColor3f(0.0f, 1.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(x-0.5f, height, y-0.5f);
	glVertex3f(x+0.5f, height, y-0.5f);
	glVertex3f(x+0.5f, height, y+0.5f);
	glVertex3f(x-0.5f, height, y+0.5f);

	// bottom
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(x-0.5f, 0.0, y-0.5f);
	glVertex3f(x+0.5f, 0.0, y-0.5f);
	glVertex3f(x+0.5f, 0.0, y+0.5f);
	glVertex3f(x-0.5f, 0.0, y+0.5f);

	// front
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(x+0.5f, 0.0f, y-0.5f);
	glVertex3f(x+0.5f, height, y-0.5f);
	glVertex3f(x-0.5f, height, y-0.5f);
	glVertex3f(x-0.5f, 0.0f, y-0.5f);

	// back
	glColor3f(0.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x-0.5f, 0.0f, y+0.5f);
	glVertex3f(x-0.5f, height, y+0.5f);
	glVertex3f(x+0.5f, height, y+0.5f);
	glVertex3f(x+0.5f, 0.0f, y+0.5f);

	// right
	glColor3f(1.0f, 1.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x+0.5f, 0.0f, y+0.5f);
	glVertex3f(x+0.5f, height, y+0.5f);
	glVertex3f(x+0.5f, height, y-0.5f);
	glVertex3f(x+0.5f, 0.0f, y-0.5f);

	// left
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x-0.5f, 0.0f, y+0.5f);
	glVertex3f(x-0.5f, height, y+0.5f);
	glVertex3f(x-0.5f, height, y-0.5f);
	glVertex3f(x-0.5f, 0.0f, y-0.5f);
	glEnd();


}


void idleFunc(){
	glutPostRedisplay();
	for (unsigned char key = 0; key != keys.size(); key++){
		if (keys[key]){
			switch (key) {
				case 'w':
					cameraPos[2]++;
					break;
				case 'a':
					cameraPos[0]++;
					break;
				case 's':
					cameraPos[2]--;
					break;
				case 'd':
					cameraPos[0]--;
					break;
				default:
					break;
			}
		}
	}

	gluLookAt(
		0.0, 5.0, 5.0,  	/* eye is at (0,0,5) */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0.);      /* up is in positive Y direction */


}

void keyboardFunc(unsigned char key, int x, int y){
	// toggle the flag for the touched key
	keys[key] = !keys[key];
}


void mouseFunc(int button, int state, int x, int y){
	// toggle the flag for the touched key
	int i=0;
}

void init(void)
{
	/* Enable a single OpenGL light.
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	*/



	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

	/* Setup the view. */
	glMatrixMode(GL_PROJECTION);
	gluPerspective(
		/* field of view in degree */ 40.0,
		/* aspect ratio */ 1.0,
		/* Z near */ 1.0,
		/* Z far */ 10.0
	);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(
		0.0, 5.0, 5.0,  	/* eye is at (0,0,5) */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0.);      /* up is in positive Y direction */

	glClearColor(0,0,0,0);

	/* Adjust cube position to be asthetic angle. */
	glTranslatef(0.0, 0.0, -1.0);
	//glRotatef(60, 1.0, 0.0, 0.0);
	//glRotatef(-20, 0.0, 0.0, 1.0);



	// show both sides of objects
	//glDisable(GL_CULL_FACE);

	// define which side to show
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	//glEnable(GL_CLIP_DISTANCE0);
}


int main(int argc, char** argv){


	cv::Mat image = loadImage(argc, argv);
	viewImage(image);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 100);
	glutCreateWindow("Hello world!");
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);

	glutMouseFunc(mouseFunc);
	glutIdleFunc(idleFunc);

	while(true){
		display();
	}

	// deprecated: glutMainLoop();

	return 0;
}
