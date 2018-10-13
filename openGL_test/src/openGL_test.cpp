/*
 * openGL_test.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */



#include <GL/glut.h>

#include <chrono>
#include <thread>


void createBlock(float x, float y, float height);

void displayMe(void){

	while(true){

		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POLYGON);
			glVertex3f(0.5, 0.0, 0.5);
			glVertex3f(0.5, 0.0, 0.0);
			glVertex3f(0.0, 0.5, 0.0);
			glVertex3f(0.0, 0.0, 0.5);
		glEnd();
		glFlush();

		glutSwapBuffers();
		glRotatef(1.0f, 1.0f, 1.0f, 1.0f);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}


void display2(void){

	// show both sides of objects
	//glDisable(GL_CULL_FACE);

	// define which side to show
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	//glEnable(GL_CLIP_DISTANCE0);





	//glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 16.0/9.0, 0.1, 100000000.0);



	while(true){


		// enable depth test
		//glClearDepth(4.0f);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		createBlock(0,0,1);

		glFlush();

		//glutSwapBuffers();
		glRotatef(1.0f, 0.0f, 1.0f, 0.0f);






		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
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


void setCam(){
	gluLookAt(
			0.0, 1.0, 1.5,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0
	);


}


int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 100);
	glutCreateWindow("Hello world!");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	setCam();


	glutDisplayFunc(display2);
	glutMainLoop();

	return 0;


}
