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



	void findWayPoints();
private:
	void draw(void);

	//void findWayPoints();
	void updateRoutes(const Wall& wall);

	// for model
	Connection corners;
	Connection waypoints;

	// only for display
	std::vector<Wall> walls;

	GLuint wallTexture;

	// keeping track of the min/max values to draw the floor with a fitting size
	Vector2 lowCorner, highCorner;

};

