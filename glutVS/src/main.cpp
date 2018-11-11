/*
 * main.cpp
 *
 *  Created on: 02.11.2018
 *      Author: rene
 */

#include "pch.h"
#include "GlutWindow.h"
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
	glutMouseFunc(mouseFunc);

	glutMainLoop();

	return 0;
}
