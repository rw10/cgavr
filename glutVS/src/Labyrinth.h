/*
 * Labyrinth.h
 *
 *  Created on: 11.11.2018
 *      Author: rene
 */

#pragma once

#include <GL/glut.h>

#include "Types.h"
#include "Wall.h"

class Labyrinth : public Drawable {
public:
	Labyrinth();
	void addWall(const Wall& wall);

private:
	void draw(void);

	Connection corners;

	std::vector<Wall> walls;

	GLuint wallTexture;

	Vector2 lowCorner, highCorner;

};

