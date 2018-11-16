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
#include <math.h>

#include "Constants.h"

Labyrinth::Labyrinth() {
	std::string file = "wall.png";
	lowCorner = Vector2(0, 0);
	highCorner = Vector2(0, 0);

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
	// add drawable wall
	walls.push_back(wall);

	// add connections
	corners[wall.begin].push_back(wall.end);
	corners[wall.end].push_back(wall.begin);

	// keep size up to date
	lowCorner.x = fmin(lowCorner.x, wall.begin.x);
	lowCorner.x = fmin(lowCorner.x, wall.end.x);
	highCorner.x = fmax(highCorner.x, wall.begin.x);
	highCorner.x = fmax(highCorner.x, wall.end.x);
	lowCorner.y = fmin(lowCorner.y, wall.begin.y);
	lowCorner.y = fmin(lowCorner.y, wall.end.y);
	highCorner.y = fmax(highCorner.y, wall.begin.y);
	highCorner.y = fmax(highCorner.y, wall.end.y);
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


	// draw floor
	glBegin(GL_QUADS);
	glColor3b(0, 0, 0);		//black
	glNormal3f(0.0f, 0.0f, 1.0f);		// view from further up
	glVertex3f(lowCorner.gl_x(), lowCorner.gl_y(), lowCorner.gl_z());
	glVertex3f(lowCorner.gl_x(), highCorner.gl_y(), lowCorner.gl_z());
	glVertex3f(highCorner.gl_x(), highCorner.gl_y(), lowCorner.gl_z());
	glVertex3f(highCorner.gl_x(), lowCorner.gl_y(), lowCorner.gl_z());

	/*
	// draw ceiling
	GLfloat height = (GLfloat) (highCorner.z + Constants::WallHeight);
	glNormal3f(0.0f, 0.0f, -1.0f);		// view from below
	glVertex3f(lowCorner.gl_x(), lowCorner.gl_y(), height);
	glVertex3f(lowCorner.gl_x(), highCorner.gl_y(), height);
	glVertex3f(highCorner.gl_x(), highCorner.gl_y(), height);
	glVertex3f(highCorner.gl_x(), lowCorner.gl_y(), height);
	*/
	glEnd();

	for (auto& wall : walls) {
		wall.draw();
	}
}


void Labyrinth::findWayPoints() {
	auto cs = corners;

	for (auto& c : cs) {
		const Vector2& corner = c.first;
		const std::vector<Vector2>& connectedCorners = c.second;
		const size_t size = connectedCorners.size();

		if (size == 1) {
			// end of a line
			// put 2 waypoint with 45° on opposite side
			
			// TODO: maybe update to 5 points?? -90, -45, 0, 45, 90
			
			Vector2 direction = corner - connectedCorners[0];
			direction.normalize(Constants::PlayerRadius);

			direction.rotateAroundZ(-90);

			int angle = 180;
			int steps = 10;
			int step = angle / steps;
			for (int i = 0; i <= angle; i+=step) {
				waypoints[corner + direction] = std::vector<Vector2>();
				addWall(Wall(corner, corner + direction, Color(0, 0, 255)));
				direction.rotateAroundZ(step);
			}
		}
		else if (size == 2) {
			// find the angle greater than 180° and put waypoint on that side
			// angle = half the given angle, dist = Constants::PlayerRadius

			Vector2 direction1 = connectedCorners[0] - corner;
			direction1.normalize(Constants::PlayerRadius);
			Vector2 direction2 = connectedCorners[1] - corner;
			direction2.normalize(Constants::PlayerRadius);

			double angle = Vector3::calcAngleInXY(direction1, direction2);

			// TODO: check angle calculation
			// acos result values are only 0 to 180!!!
			bool left = angle < 0;

			if (left) {
				angle += 180;
				direction2.rotateAroundZ(-90);
			}
			else {
				direction2.rotateAroundZ(90);
			}

			int steps = 10;
			int step = angle / steps;
			for (int i = 0; i <= angle; i += step) {
				waypoints[corner + direction2] = std::vector<Vector2>();
				addWall(Wall(corner, corner + direction2, Color(0, 0, 255)));

				if (left) {
					direction2.rotateAroundZ(-step);
				}
				else {
					direction2.rotateAroundZ(step);
				}
			}

				/*
			if (angle < 180) {
				direction2.rotateAroundZ((360-angle) / 2);
			}
			else {
				direction2.rotateAroundZ(angle / 2);
			}

			direction2.normalize(Constants::PlayerRadius);
			Vector2 waypoint = corner + direction2;
			waypoints[waypoint] = std::vector<Vector2>();

			addWall(Wall(corner, waypoint, Color(0, 0, 255)));
			*/
		}
		else{
			// TODO: find the angles that combine to 360°. Use all connections combined, not only pairwise!!
			// if there is an angle greater than 180°, put a waypoint on that side
		}
	}

	for (auto w : waypoints) {
	}
}
