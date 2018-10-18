/*
 * DisplayImage.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */


#include <opencv2/opencv.hpp>

using namespace cv;

Mat loadImage( int argc, char** argv ){
	Mat image;

	if(argc != 2){
		printf( "No image file specified \n" );
		return image;
	}
	image = imread( argv[1], 1 );
	if(!image.data){
		printf( "No image data \n" );
		return image;
	}

	return image;
}

void viewImage(Mat image){
	namedWindow( "Display Image", WINDOW_AUTOSIZE );
	imshow( "Display Image", image );
	waitKey(0);
}

int main( int argc, char** argv )
{
	Mat image = loadImage(argc, argv);
	viewImage(image);





	return 0;
}

