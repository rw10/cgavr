/*
 * main.cpp
 *
 *  Created on: 02.11.2018
 *      Author: rene
 */

#include "pch.h"
#include "GlutWindow.h"

#define PI = 3.14159;

void display() {
	GlutWindow::get().display();
}

void idleFunc() {
	GlutWindow::get().idleFunc();

	// trigger repaint on next turn
	//glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y) {
	GlutWindow::get().keyboardFunc(key, x, y);
}
void keyboardUpFunc(unsigned char key, int x, int y) {
	GlutWindow::get().keyboardUpFunc(key, x, y);
}

void specialFunc(int key, int x, int y) {
	unsigned char k = static_cast<unsigned char>(key);
	GlutWindow::get().specialFunc(k, x, y);
}
void specialUpFunc(int key, int x, int y) {
	unsigned char k = static_cast<unsigned char>(key);
	GlutWindow::get().specialUpFunc(k, x, y);
}

void mouseFunc(int button, int state, int x, int y) {
	GlutWindow::get().mouseFunc(button, state, x, y);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	
	GlutWindow::init();

	glutDisplayFunc(display);
	glutIdleFunc(idleFunc);

	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutSpecialFunc(specialFunc);
	glutSpecialUpFunc(specialUpFunc);
	glutMouseFunc(mouseFunc);

	glutMainLoop();

	return 0;
}
