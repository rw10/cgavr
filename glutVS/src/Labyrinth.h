/*
 * Labyrinth.h
 *
 *  Created on: 11.11.2018
 *      Author: rene
 */

#pragma once


#include "Types.h"
#include "WayPoint.h"
#include "Wall.h"


class Labyrinth : public Drawable {
public:
	Labyrinth();
	~Labyrinth();

	friend class WayPoint;

	void addWall(const Wall& wall);
	void addWall(const Vector3& begin, const Vector3& end);


	void initRouting();
	void calculateRoute(const Vector2& start, const Vector2& end);
private:
	Vector2 startPoint;
	Vector2 endPoint;

	virtual void draw(void) const;
	void drawFloor(void) const;

	// for model
	/*
	* this map contains the labyrinth walls
	* the key is created by all points that serve as a corner (unique)
	* each corner has list of all points it is connected to (which all are a corner-points themself)
	*/
	ConnectedNetwork corners;

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
	ConnectedNetwork routes;

	// only for display
	std::vector<Wall> walls;
	std::vector<Wall> wayPointWalls;
	std::vector<Wall> autoRouteWalls;
	std::vector<Wall> lvl1RouteWalls;
	std::vector<Wall> lvl1DeniedRouteWalls;
	std::vector<Wall> lvl2RouteWalls;
	std::vector<Wall> lvl2DeniedRouteWalls;
	std::vector<Wall> additionalRouteWalls;
	std::vector<Wall> additionalDeniedRouteWalls;
	std::vector<Wall> dijkstraRoute;


	// keeping track of the min/max values to draw the floor with a fitting size
	Vector2 lowCorner, highCorner;

};

