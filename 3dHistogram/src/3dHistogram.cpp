/*
 * 3dHistogram.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */


#include "3dHistogram.h"

// image container
cv::Mat image;

int rotation = 0;

// bools for each key, init with all false
std::vector<bool> keys(256,false);

std::vector<float> cameraPos = {0.0f, 5.0f, 5.0f};

cv::Mat loadImage( int argc, char** argv ){
	cv::Mat img;

	if(argc != 2){
		printf( "No image file specified \n" );
		return img;
	}
	img = cv::imread( argv[1], cv::IMREAD_UNCHANGED); //IMREAD_GRAYSCALE );

	return img;
}

void viewImage(cv::Mat& img){
	cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
	cv::imshow( "Display Image", img );
	cv::waitKey(0);
}


void displayBlock(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	createBlock(
			0,0,1,
			1,1,1,
			255,0,0
	);
	glutSwapBuffers();


	//glRotatef(1.0f, 0.0f, 1.0f, 0.0f);

	glFlush();


	// force repaint
	glutPostRedisplay();
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawHistogram3D(image);

	glutSwapBuffers();

	rotation = (rotation+1) % 180;

	if (rotation<45 || rotation >= 135){
		glRotatef(4.0f, 0.0f, 1.0f, 0.0f);
	}
	else{
		glRotatef(-4.0f, 0.0f, 1.0f, 0.0f);
	}

	glFlush();


	// force repaint
	glutPostRedisplay();
}

void DrawHistogram3D(cv::Mat& image)
{
	cv::Size s = image.size();
	int rows = s.height;
	int cols = s.width;

	double maxHeight = 20.0;

	double widthX = 20;
	double widthY = 20;
	double dx = 2*widthX / rows;
	double dy = 2*widthY / cols;

	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++)
		{
			//unsigned char z = image.at<unsigned char>(x,y);
			//unsigned char a = 255;

			// 4 values in png, rgba
			cv::Vec4b intensity = image.at<cv::Vec4b>(x, y);
			unsigned char b = intensity.val[0];
			unsigned char g = intensity.val[1];
			unsigned char r = intensity.val[2];
			unsigned char a = intensity.val[3];

			unsigned char z = (r+g+b)/3.0;

			float height = maxHeight*z/255.0;

			// skip if alpha too low
			if (a > 30){
				createBlock(
						-widthY+y*dy, -widthX+x*dx, height,		// position
						dy, dx,	maxHeight,						// max size
						r, g, b									// color
				);
				//std::cout << std::to_string(z) << " ";
			}
		}
		//std::cout << "row: " << (x+1) << "/" << rows << std::endl;
	}
}



void createBlock(
		float x, float y, float height,
		double deltaX, double deltaY, double maxHeight,
		unsigned char r, unsigned char g, unsigned char b
){

	glBegin(GL_QUADS);
	// top
	glColor3ub(r,g,b);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x-deltaX, height, y-deltaY);
	glVertex3f(x+deltaX, height, y-deltaY);
	glVertex3f(x+deltaX, height, y+deltaY);
	glVertex3f(x-deltaX, height, y+deltaY);

	// bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(x-deltaX, 0.0, y-deltaY);
	glVertex3f(x+deltaX, 0.0, y-deltaY);
	glVertex3f(x+deltaX, 0.0, y+deltaY);
	glVertex3f(x-deltaX, 0.0, y+deltaY);

	// front
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(x+deltaX, 0.0f, y-deltaY);
	glVertex3f(x+deltaX, height, y-deltaY);
	glVertex3f(x-deltaX, height, y-deltaY);
	glVertex3f(x-deltaX, 0.0f, y-deltaY);

	// back
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x-deltaX, 0.0f, y+deltaY);
	glVertex3f(x-deltaX, height, y+deltaY);
	glVertex3f(x+deltaX, height, y+deltaY);
	glVertex3f(x+deltaX, 0.0f, y+deltaY);

	// right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x+deltaX, 0.0f, y+deltaY);
	glVertex3f(x+deltaX, height, y+deltaY);
	glVertex3f(x+deltaX, height, y-deltaY);
	glVertex3f(x+deltaX, 0.0f, y-deltaY);

	// left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(x-deltaX, 0.0f, y+deltaY);
	glVertex3f(x-deltaX, height, y+deltaY);
	glVertex3f(x-deltaX, height, y-deltaY);
	glVertex3f(x-deltaX, 0.0f, y-deltaY);
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


}

void keyboardFunc(unsigned char key, int x, int y){
	// toggle the flag for the touched key
	keys[key] = !keys[key];
}


void mouseFunc(int button, int state, int x, int y){
	// toggle the flag for the touched key

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
		/* Z far */ 1000.0
	);
	glMatrixMode(GL_MODELVIEW);

	gluLookAt(
		0.0, 80.0, 30.0,  	/* eye is at (0,5,5) */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0.0
	);      /* up is in positive Y direction */

	glClearColor(0.0,0.1,0.4,1);

	/* Adjust cube position to be asthetic angle. */
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

	image = loadImage(argc, argv);
	viewImage(image);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 100);
	glutCreateWindow("3D Histogram");
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);

	glutMouseFunc(mouseFunc);
	glutIdleFunc(idleFunc);

	// any key (with focus on original pic) to stop
	// space key = 32
	int key = -1;
	while(key == -1){
 		key = cv::waitKey(100);
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		display();
	}

	// deprecated: glutMainLoop();

	return 0;
}
