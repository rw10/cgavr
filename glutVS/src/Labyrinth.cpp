/*
 * Labyrinth.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */

#include "pch.h"

#include "Labyrinth.h"

#include <iostream>
#include <SOIL.h>

Labyrinth::Labyrinth() {
	std::string file = "wall.png";

	/* load an image file directly as a new OpenGL texture */
	wallTexture = SOIL_load_OGL_texture
	(
		file.data(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	if (wallTexture == 0) {
		std::cout << "error reading file: " << file.data() << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, wallTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Labyrinth::addWall(const Wall& wall){
	walls.push_back(wall);
}

void Labyrinth::draw(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	// enable texture
	//glGenTextures(1, &wallTexture);
	glBindTexture(GL_TEXTURE_2D, wallTexture);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	glBegin(GL_QUADS);
	// floor
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 10);
	glVertex3f(0, 100, 10);
	glVertex3f(100, 100, 10);
	glVertex3f(100, 0, 10);
	glEnd();

	for (auto& wall : walls) {
		wall.draw();
	}
}
