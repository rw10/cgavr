#pragma once

#include "Vector2.h"
#include <vector>
#include "Types.h"

// declare the Labyrinth-class
class Labyrinth;

class WayPoint {
public:
	WayPoint(){}
	~WayPoint(){}

	Vector2 main;
	std::vector<Vector2> others;

	std::vector<Vector2> getAll() const {
		std::vector<Vector2> all = others;
		all.push_back(main);
		return all;
	}

	static void buildRoutingNetwork(Labyrinth& lab) {
		findWayPoints(lab);
		testAllRoutes(lab);
	}

	static ConnectedNetwork connectPointsToNetwork(const std::vector<Vector2>& point, const ConnectedNetwork& routeNetwork, Labyrinth& lab);

private:
	// step 1: find waypoints on the corners
	static void findWayPoints(Labyrinth& lab);
	static WayPoint createWaypointsAroundCorner(const Vector2& corner, double angle, Vector2 directionVector, unsigned int count, Labyrinth& lab);

	// step2: create Routes by connecting the waypoints
	static void testAllRoutes(Labyrinth& lab);
	static void testAllSubRoutes(const WayPoint& wp1, const WayPoint& wp2, Labyrinth& lab);
	static void createRoute(const Vector2& wp1, const Vector2& wp2, ConnectedNetwork& routes);

};