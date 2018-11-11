/*
 * Labyrinth.h
 *
 *  Created on: 11.11.2018
 *      Author: rene
 */

#pragma once

#include <vector>

#include "Wall.h"

class Labyrinth : public Drawable {
public:
	Labyrinth();
	void addWall(const Wall& wall);

private:
	void draw(void);

	std::vector<Wall> walls;
};

