/*
 * main.cpp
 *
 *  Created on: 02.11.2018
 *      Author: rene
 */

#include "pch.h"
#include "GlutWindow.h"

void display() {
	GlutWindow::get(1).display();
}
void display2() {
	GlutWindow::get(2).display();
}

void idleFunc() {
	GlutWindow::get(1).idleFunc();

	// toggle the windows
	GlutWindow::toggle();
}

void keyboardFunc(unsigned char key, int x, int y) {
	GlutWindow::get(1).keyboardFunc(key, x, y);
}
void keyboardUpFunc(unsigned char key, int x, int y) {
	GlutWindow::get(1).keyboardUpFunc(key, x, y);
}

void specialFunc(int key, int x, int y) {
	unsigned char k = static_cast<unsigned char>(key);
	GlutWindow::get(1).specialFunc(k, x, y);
}
void specialUpFunc(int key, int x, int y) {
	unsigned char k = static_cast<unsigned char>(key);
	GlutWindow::get(1).specialUpFunc(k, x, y);
}

void mouseFunc(int button, int state, int x, int y) {
	GlutWindow::get(1).mouseFunc(button, state, x, y);
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

	GlutWindow::init();

	// only the display will be different on window2, all actions will be sent to window1
	glutDisplayFunc(display2);

	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutSpecialFunc(specialFunc);
	glutSpecialUpFunc(specialUpFunc);
	glutMouseFunc(mouseFunc);

	glutMainLoop();

	return 0;
}
