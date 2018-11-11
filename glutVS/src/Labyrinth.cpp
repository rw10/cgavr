/*
 * Labyrinth.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */

#include "pch.h"

#include "Labyrinth.h"

Labyrinth::Labyrinth() {}

void Labyrinth::addWall(const Wall& wall){
	walls.push_back(wall);
}

void Labyrinth::draw(void)
{
	for (auto& wall : walls) {
		wall.draw();
	}
}
