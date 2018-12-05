/*
 * main.cpp
 *
 *  Created on: 02.11.2018
 *      Author: rene
 */

#include "GlutWindow.h"
#include "Receiver.h"
#include "Sender.h"

void display() {
	GlutWindow::get(0).display();
}
void display2() {
	GlutWindow::get(1).display();
}

void idleFunc() {
	GlutWindow::get(0).idleFunc();

	// toggle the windows
	GlutWindow::toggle();
}

void keyboardFunc(unsigned char key, int x, int y) {
	GlutWindow::get(0).keyboardFunc(key, x, y);
}
void keyboardUpFunc(unsigned char key, int x, int y) {
	GlutWindow::get(0).keyboardUpFunc(key, x, y);
}

void specialFunc(int key, int x, int y) {
	unsigned char k = static_cast<unsigned char>(key);
	GlutWindow::get(0).specialFunc(k, x, y);
}
void specialUpFunc(int key, int x, int y) {
	unsigned char k = static_cast<unsigned char>(key);
	GlutWindow::get(0).specialUpFunc(k, x, y);
}

void mouseFunc(int button, int state, int x, int y) {
	GlutWindow::get(0).mouseFunc(button, state, x, y);
}

void connectCallbacks() {
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutSpecialFunc(specialFunc);
	glutSpecialUpFunc(specialUpFunc);
	glutMouseFunc(mouseFunc);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	
	GlutWindow::init();
	glutDisplayFunc(display);
	connectCallbacks();

	GlutWindow::init();
	// only the display will be different on window2, all events will be sent to window1
	glutDisplayFunc(display2);
	connectCallbacks();

	Receiver::init();
	Sender::init();

	glutMainLoop();

	return 0;
}
