/*
 * Labyrinth.h
 *
 *  Created on: 11.11.2018
 *      Author: rene
 */

#pragma once

#include "Wall.h"
#include <vector>
#include <GL/glut.h>

class Labyrinth : public Drawable {
public:
	Labyrinth();
	void addWall(const Wall& wall);

private:
	void draw(void);


	std::vector<Corner> corners;

	std::vector<Wall> walls;

	GLuint wallTexture;
};

