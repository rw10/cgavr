/*
 * 3dHistogram.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */



#include "Block.h"

#include "Histogram3D.h"

Histogram3D::Histogram3D(std::string file) {
	loadImage(file);
	viewImage();
	createList();
}

void Histogram3D::loadImage(const std::string& file) {
	image = cv::imread(file, cv::IMREAD_UNCHANGED); //IMREAD_GRAYSCALE );
}

void Histogram3D::viewImage() {
	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image", image);
	//cv::waitKey(0);
}

void Histogram3D::createList()
{
	cv::Size s = image.size();
	int rows = s.height;
	int cols = s.width;

	blocks = std::vector<Block>(rows*cols);

	double maxHeight = 20.0;

	double widthX = 20;
	double widthY = 20;
	double dx = 2 * widthX / cols;
	double dy = 2 * widthY / rows;

	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			//unsigned char z = image.at<unsigned char>(x,y);
			unsigned char a = 255;

			// 4 values in png, rgba
			cv::Vec3b intensity = image.at<cv::Vec3b>(y, x);
			unsigned char b = intensity.val[0];
			unsigned char g = intensity.val[1];
			unsigned char r = intensity.val[2];
			//unsigned char a = intensity.val[3];

			unsigned char z = (r + g + b) / 3;

			double height = maxHeight * z / 255.0;

			// skip if alpha too low
			if (a > 30) {
				blocks.push_back(
					Block::createByCenterSize(
						Vector3(
							x*dx - widthX, 
							-y*dy + widthY,			// turn y because in openCV the y=0 is at the top
							height / 2
						),
						Vector3(dx, dy, height),
						Color3ub(r, g, b)
					)
				);
				//std::cout << std::to_string(z) << " ";
			}
		}
		//std::cout << "row: " << (x+1) << "/" << rows << std::endl;
	}
}

void Histogram3D::animate(const double time)
{
	for (auto& block : blocks) {
		block.animate(time);
	}
}

void Histogram3D::draw(void) const
{
	// nothing to do
	// drawn by parts
}
