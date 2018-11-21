/*
 * Labyrinth.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */

#include "pch.h"

#include "Labyrinth.h"

#include <iostream>
#include <math.h>
#include <algorithm>

#include "Collision.h"
#include "Settings.h"
#include "Textures.h"

Labyrinth::Labyrinth() {
	lowCorner = Vector2(0, 0);
	highCorner = Vector2(0, 0);
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

void Labyrinth::addWall(const Vector3& begin, const Vector3& end) {
	addWall(Wall(begin, end, Textures::get().wallTexture));
}

void Labyrinth::draw(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	drawFloor();

	for (auto& wall : walls) {
		wall.draw();
	}


	// draw auxiliary walls
	if (Settings::wayPointWalls.show) {
		for (auto& wall : wayPointWalls) {
			wall.draw();
		}
	}
	if (Settings::autoRouteWalls.show) {
		for (auto& wall : autoRouteWalls) {
			wall.draw();
		}
	}
	if (Settings::lvl1RouteWalls.show) {
		for (auto& wall : lvl1RouteWalls) {
			wall.draw();
		}
	}
	if (Settings::lvl1DeniedRouteWalls.show) {
		for (auto& wall : lvl1DeniedRouteWalls) {
			wall.draw();
		}
	}
	if (Settings::lvl2RouteWalls.show) {
		for (auto& wall : lvl2RouteWalls) {
			wall.draw();
		}
	}
	if (Settings::lvl2DeniedRouteWalls.show) {
		for (auto& wall : lvl2DeniedRouteWalls) {
			wall.draw();
		}
	}
}

void Labyrinth::drawFloor() {

	// enable texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Textures::get().groundTexture);
	// use repeat mode for wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLfloat textureSizeX = (GLfloat)(highCorner.gl_x() / Settings::TextureSizeMultiplier);
	GLfloat textureSizeY = (GLfloat)(highCorner.gl_y() / Settings::TextureSizeMultiplier);

	// draw floor
	glBegin(GL_QUADS);
	glColor3b(50, 50, 50);		//grey
	glNormal3f(0.0f, 0.0f, 1.0f);		// view from further up

	// bottom left
	glTexCoord2f(0, 0);
	glVertex3f(lowCorner.gl_x(), lowCorner.gl_y(), lowCorner.gl_z());

	// bottom right
	glTexCoord2f(textureSizeX, 0);
	glVertex3f(highCorner.gl_x(), lowCorner.gl_y(), lowCorner.gl_z());

	// top right
	glTexCoord2f(textureSizeX, textureSizeY);
	glVertex3f(highCorner.gl_x(), highCorner.gl_y(), lowCorner.gl_z());

	// top left
	glTexCoord2f(0, textureSizeY);
	glVertex3f(lowCorner.gl_x(), highCorner.gl_y(), lowCorner.gl_z());

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
}

WayPoint Labyrinth::createWaypointsAroundCorner(const Vector2& corner, double angle, Vector2 directionVector, unsigned int nrPointsOnEitherSide) {

	bool left = angle < 0;
	directionVector.normalize(Settings::PlayerRadius);

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
	wayPointWalls.push_back(Wall(corner, middleVector, Settings::wayPointWalls.color));
	wp.main = middleVector;

	Vector2 prevL = middleVector;
	Vector2 prevR = middleVector;

	// create n waypoints on circular path around the corner
	for (size_t i = 1; i <= nrPointsOnEitherSide; i++) {
		double step = i * angle / nrPointsOnEitherSide;

		// add a waypoint to the left
		Vector2 leftVec = directionVector;
		leftVec.rotateAroundZ(-step);
		leftVec = Vector2(corner + leftVec);
		wayPointWalls.push_back(Wall(corner, leftVec, Settings::wayPointWalls.color * 2));

		// add a waypoint to the right
		Vector2 rightVec = directionVector;
		rightVec.rotateAroundZ(step);
		rightVec = Vector2(corner + rightVec);
		wayPointWalls.push_back(Wall(corner, rightVec, Settings::wayPointWalls.color * 2));

		// add to corner-waypoint
		wp.others.push_back(leftVec);
		wp.others.push_back(rightVec);

		// connect the waypoints that are next to each other
		connectWaypoints(prevL, leftVec);
		autoRouteWalls.push_back(Wall(prevL, leftVec, Settings::autoRouteWalls.color));
		prevL = leftVec;
		connectWaypoints(prevR, rightVec);
		autoRouteWalls.push_back(Wall(prevR, rightVec, Settings::autoRouteWalls.color));
		prevR = rightVec;
	}

	return wp;
	
	// TODO: save circle-around-the-corner-distance instead of euclidean 
	
}


void Labyrinth::connectWaypoints(const Vector2& wp1, const Vector2& wp2) {
	routes[wp1].push_back(wp2);
	routes[wp2].push_back(wp1);
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
			
			// TODO:
			// 2 of the points should be the same, but are not due to rounding errors
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
			// find the angles that combine to 360°. Use all connections combined, not only pairwise!!
			// if there is an angle greater than 180°, put a waypoint on that side

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


void Labyrinth::testAllRoutes() {

	for (size_t i = 0; i < waypoints.size(); i++) {
		const auto& wp1 = waypoints[i];

		// start with j=i, so we don't double check
		for (size_t j = i; j < waypoints.size(); j++) {
			const auto& wp2 = waypoints[j];
			bool collision = false;

			// test all walls (or until a collision is found)
			for (size_t w = 0; !collision && w < walls.size(); w++) {
				const auto& wall = walls[w];
				// or connection -> one collision shall prevent the connection
				collision |= Collision::isColliding(wp1.main, wp2.main, wall);
			}

			if (!collision) {
				testAllSubRoutes(wp1, wp2);
				lvl1RouteWalls.push_back(Wall(wp1.main, wp2.main, Settings::lvl1RouteWalls.color));
			}
			else {
				lvl1DeniedRouteWalls.push_back(Wall(wp1.main, wp2.main, Settings::lvl1DeniedRouteWalls.color));
			}
		}
	}
}

void Labyrinth::testAllSubRoutes(const WayPoint& wp1, const WayPoint& wp2) {
	const auto& list1 = wp1.getAll();
	const auto& list2 = wp2.getAll();

	for (size_t i = 0; i < list1.size(); i++) {
		const auto& point1 = list1[i];
		for (size_t j = 0; j < list2.size(); j++) {
			const auto& point2 = list2[j];
			bool collision = false;

			// test all walls (or until a collision is found)
			for (size_t w = 0; !collision && w < walls.size(); w++) {
				const auto& wall = walls[w];
				// or connection -> one collision shall prevent the connection
				collision |= Collision::isColliding(point1, point2, wall);

				// check collision with player body
				collision |= Collision::findClosestDistance(point1, point2, wall) < Settings::PlayerRadius * 0.99;
			}

			if (!collision) {
				connectWaypoints(point1, point2);
				lvl2RouteWalls.push_back(Wall(point1, point2, Settings::lvl2RouteWalls.color));
			}
			else {
				lvl2DeniedRouteWalls.push_back(Wall(point1, point2, Settings::lvl2DeniedRouteWalls.color));
			}
		}
	}
}
