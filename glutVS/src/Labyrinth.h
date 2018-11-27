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
#include "Cylinder.h"
#include "Dijkstra.h"

enum WallType {
	MAINWAYPOINT, WAYPOINT, AUTO, LVL1, LVL1DENIED, LVL2, LVL2DENIED, ADDITIONAL, ADDITIONALDENIED, DIJKSTRA
};

class Labyrinth : public Drawable {
public:
	Labyrinth();
	~Labyrinth();

	friend class WayPoint;

	void addWall(const Vector3& begin, const Vector3& end);
	void addHelperLine(const Vector3& begin, const Vector3& end, WallType type);

	void initRouting();
	Dijkstra calculateRoute(const Vector2& start, const Vector2& end);

	virtual void show(const double time, const ViewSettings& viewSettings);
	virtual void animate(const double time);

protected:
	virtual void draw(void) const;

private:
	void addWall(const Wall& wall);

	// dijkstra start and end point
	Vector2 startPoint;
	Vector2 endPoint;

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

	std::map<Vector2, Cylinder> roundCorners;

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

