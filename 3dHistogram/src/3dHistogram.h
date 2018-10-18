/*
 * 3dHistogram.h
 *
 *  Created on: 17.10.2018
 *      Author: rene
 */

#ifndef SRC_3DHISTOGRAM_H_
#define SRC_3DHISTOGRAM_H_


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

cv::Mat loadImage( int argc, char** argv );
void viewImage(cv::Mat& img);

void displayBlock(void);
void display();

void DrawHistogram3D(cv::Mat& image);
void createBlock(
		float x, float y, float height,
		double deltaX, double deltaY, double maxHeight,
		unsigned char r, unsigned char g, unsigned char b
);


void idleFunc();
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);

void init(void);


#endif /* SRC_3DHISTOGRAM_H_ */
