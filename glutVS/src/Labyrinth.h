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

	WayPoint createWaypointsAroundCorner(const Vector2& corner, double angle, Vector2 directionVector, unsigned int count);
	void connectWaypoints(const Vector2& wp1, const Vector2& wp2);

	// for model
	/*
	* this map contains the labyrinth walls
	* the key is created by all points that serve as a corner (unique)
	* each corner has list of all points it is connected to (which all are a corner-points themself)
	*/
	Connection corners;

	/*
	* this vector contains the waypoints that were built around a corner point
	* they are grouped as structures for each corner they originate from
	* they have a 'main' point that should be viewable from other 'main' points, if any of those points are connected
	*/
	std::vector<WayPoint> waypoints;

	/*
	* this vector contains the possible routes
	* the key is created by all points that could be reached by the player (unique)
	* each point has list of all other reachable points it is connected to
	*/
	Connection routes;

	// only for display
	std::vector<Wall> walls;

	GLuint wallTexture;

	// keeping track of the min/max values to draw the floor with a fitting size
	Vector2 lowCorner, highCorner;

};

