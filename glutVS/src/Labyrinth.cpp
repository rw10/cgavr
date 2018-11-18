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
#include <algorithm>

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

WayPoint Labyrinth::createWaypointsAroundCorner(const Vector2& corner, double angle, Vector2 directionVector, unsigned int nrPointsOnEitherSide) {

	bool left = angle < 0;
	directionVector.normalize(Constants::PlayerRadius);

	// use side with angle>180°
	// waypoints on cirle around the point, limited by right angle to the direction vectors
	// angle is half the angle in between these points
	angle = (180 - abs(angle)) / 2;

	// put into middle position
	if (left) {
		directionVector.rotateAroundZ(-90-angle);
	}
	else {
		directionVector.rotateAroundZ(90+angle);
	}

	// build a corner-waypoint
	WayPoint wp;

	// add a waypoint in the middle
	Vector2 middleVector = corner + directionVector;
	addWall(Wall(corner, middleVector, Color(0, 0, 255)));
	wp.main = middleVector;

	Vector2 prevL = middleVector;
	Vector2 prevR = middleVector;

	// create n waypoints on circular path around the corner
	for (int i = 1; i <= nrPointsOnEitherSide; i++) {
		double step = i * angle / nrPointsOnEitherSide;

		// add a waypoint to the left
		Vector2 leftVec = directionVector;
		leftVec.rotateAroundZ(-step);
		leftVec = Vector2(corner + leftVec);
		addWall(Wall(corner, leftVec, Color(0, 0, 255)));

		// add a waypoint to the right
		Vector2 rightVec = directionVector;
		rightVec.rotateAroundZ(step);
		rightVec = Vector2(corner + rightVec);
		addWall(Wall(corner, rightVec, Color(0, 0, 255)));

		// add to corner-waypoint
		wp.others.push_back(leftVec);
		wp.others.push_back(rightVec);

		// connect the waypoints that are next to each other
		connectWaypoints(prevL, leftVec);
		prevL = leftVec;
		connectWaypoints(prevR, rightVec);
		prevR = rightVec;
	}

	return wp;
	
	// TODO: use circle-around-the-corner-distance instead of euclidean
	
}


void Labyrinth::connectWaypoints(const Vector2& wp1, const Vector2& wp2) {
	routes[wp1].push_back(wp2);
	routes[wp2].push_back(wp1);
	addWall(Wall(wp1, wp2, Color(0, 255, 0)));
}


void Labyrinth::findWayPoints() {
	auto cs = corners;

	for (auto& c : cs) {
		const Vector2& corner = c.first;
		const std::vector<Vector2>& connectedCorners = c.second;
		const size_t size = connectedCorners.size();

		if (size == 1) {
			// = end of a line
			// put 2 waypoint with 45° on opposite side
			Vector2 direction = connectedCorners[0] - corner;

			// call 2 times -> 45° points have to be main point in Waypoint structure
			WayPoint wp1 = createWaypointsAroundCorner(corner, 90, direction, 1);
			waypoints.push_back(wp1);
			WayPoint wp2 = createWaypointsAroundCorner(corner, -90, direction, 1);
			waypoints.push_back(wp2);
			
			// should be the same points, but are not due to rounding errors
			// option 1: connect
			//connectWaypoints(*wp1.others.rbegin(), *wp2.others.begin());
			// 2: overwrite one with the others value, and transfer the connections
			// 3: round values inside the creation
			// 4: leave it at that, will be connected during main phase anyway
		}
		else if (size == 2) {
			// find the angle greater than 180° and put waypoints on that side
			// angle = half the given angle, dist = Constants::PlayerRadius

			Vector2 direction1 = connectedCorners[0] - corner;
			Vector2 direction2 = connectedCorners[1] - corner;

			double angle = Vector3::calcAngleInXY(direction1, direction2);
			WayPoint wp = createWaypointsAroundCorner(corner, angle, direction2, 1);
			waypoints.push_back(wp);
		}
		else{
			// TODO: find the angles that combine to 360°. Use all connections combined, not only pairwise!!
			// if there is an angle greater than 180°, put a waypoint on that side

			//  TODO:
			// start with one direction
			// calc all angles to other directions
			// negative values = 360-angle
			// if the smallest is > 180, there is an angle to use

			bool found = false;

			for (int i = 0; !found && i < connectedCorners.size(); i++) {
				std::vector<double> angles;
				Vector2 direction1 = connectedCorners[i] - corner;
				for (int j = 0; !found && j < connectedCorners.size(); j++) {
					if (i != j) {
						Vector2 direction2 = connectedCorners[j] - corner;
						double angle = Vector3::calcAngleInXY(direction1, direction2);
						if (angle < 0) {
							angle += 360;
						}

						angles.push_back(angle);
					}				
				}

				std::sort(angles.begin(), angles.end());

				// use 0.01 as buffer for inaccuracy in calculation
				if (angles[0] > 180.01) {
					WayPoint wp = createWaypointsAroundCorner(corner, 360 - angles[0], direction1, 1);
					waypoints.push_back(wp);
				}
			}

		}
	}
}
