/*
 * 3dHistogram.h
 *
 *  Created on: 17.10.2018
 *      Author: rene
 */

#pragma once

#include <string>
#include <opencv2/opencv.hpp>

#include "Block.h"

class Histogram3D : public Drawable{
public:

	Histogram3D(std::string file = "D:\\image.jpg");

	void animate(const double time);

protected:
	virtual void draw(void) const;

private:
	void loadImage(const std::string& file);
	void viewImage();
	void createList();

	std::vector<Block> blocks;

	// image container
	cv::Mat image;
};