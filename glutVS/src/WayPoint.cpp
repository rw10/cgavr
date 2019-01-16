/*
 * Labyrinth.cpp
 *
 *  Created on: 22.11.2018
 *      Author: rene
 */



#include "WayPoint.h"

#include "Labyrinth.h"
#include "Settings.h"
#include "Collision.h"
#include <algorithm>


WayPoint WayPoint::createWaypointsAroundCorner(const Vector2& corner, double angle, Vector2 directionVector, size_t detail, Labyrinth& lab) {

	size_t nrPointsOnEitherSide = 1 + detail;

	bool left = angle > 180;
	directionVector.normalize(Settings::PlayerRadius + Settings::WallWidth);

	if (left) {
		angle = 360 - angle;
	}

	// use side with angle>180°
	// waypoints on cirle around the point, limited by right angle to the direction vectors
	// angle is half the angle in between these points
	angle = (180 - abs(angle)) / 2;

	// put into middle position
	if (left) {
		directionVector.rotateAroundZ(-90 - angle);
	}
	else {
		directionVector.rotateAroundZ(90 + angle);
	}

	// build a corner-waypoint
	WayPoint wp;

	// add a waypoint in the middle
	Vector2 middleVector = corner + directionVector;
	lab.addHelperLine(corner, middleVector, WallType::MAINWAYPOINT);
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
		lab.addHelperLine(corner, leftVec, WallType::WAYPOINT);

		// add a waypoint to the right
		Vector2 rightVec = directionVector;
		rightVec.rotateAroundZ(step);
		rightVec = Vector2(corner + rightVec);
		lab.addHelperLine(corner, rightVec, WallType::WAYPOINT);

		// add to corner-waypoint
		wp.others.push_back(leftVec);
		wp.others.push_back(rightVec);

		// connect the waypoints that are next to each other		
		if (!Collision::isColliding(prevL, leftVec, lab.walls, CollisionTestType::WALL_WIDTH_ONLY)) {
			createRoute(prevL, leftVec, lab.routes);
			lab.addHelperLine(prevL, leftVec, WallType::AUTO);
		}
		prevL = leftVec;
		if (!Collision::isColliding(prevR, rightVec, lab.walls, CollisionTestType::WALL_WIDTH_ONLY)) {
			createRoute(prevR, rightVec, lab.routes);
			lab.addHelperLine(prevR, rightVec, WallType::AUTO);
		}
		prevR = rightVec;
	}

	return wp;

	// TODO: save circle-around-the-corner-distance instead of euclidean 

}


void WayPoint::findWayPoints(Labyrinth& lab) {
	for (const auto& c : lab.corners) {
		const Vector2& corner = c.first;
		const auto& connectedCorners = c.second;
		const size_t size = connectedCorners.size();

		if (size == 1) {
			// = end of a line
			// put 2 waypoint with 45° on opposite side
			Vector2 direction = connectedCorners[0] - corner;

			// call 2 times -> 45° points have to be main point in Waypoint structure
			WayPoint wp1 = createWaypointsAroundCorner(corner, 90, direction, Settings::WayPointDetail, lab);
			lab.waypoints.push_back(wp1);
			WayPoint wp2 = createWaypointsAroundCorner(corner, 270, direction, Settings::WayPointDetail, lab);
			lab.waypoints.push_back(wp2);

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
			WayPoint wp = createWaypointsAroundCorner(corner, angle, direction2, Settings::WayPointDetail, lab);
			lab.waypoints.push_back(wp);
		}
		else {
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
				for (int j = 0; j < connectedCorners.size(); j++) {
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
					found = true;
					WayPoint wp = createWaypointsAroundCorner(corner, 360 - angles[0], direction1, Settings::WayPointDetail, lab);
					lab.waypoints.push_back(wp);
				}
			}
		}
	}
}



void WayPoint::testAllRoutes(Labyrinth& lab) {

	for (size_t i = 0; i < lab.waypoints.size(); i++) {
		const auto& wp1 = lab.waypoints[i];

		// start with j=i, so we don't double check
		for (size_t j = i; j < lab.waypoints.size(); j++) {
			const auto& wp2 = lab.waypoints[j];

			// check points for visibility
			// an additional collision test using distance to wall may not be used here!!
			bool collision = Collision::isColliding(wp1.main, wp2.main, lab.walls, CollisionTestType::VISIBILITY);

			if (!collision) {
				testAllSubRoutes(wp1, wp2, lab);
				lab.addHelperLine(wp1.main, wp2.main, WallType::LVL1);
			}
			else {
				lab.addHelperLine(wp1.main, wp2.main, WallType::LVL1DENIED);
			}
		}
	}
}

void WayPoint::testAllSubRoutes(const WayPoint& wp1, const WayPoint& wp2, Labyrinth& lab) {
	const auto& list1 = wp1.getAll();
	const auto& list2 = wp2.getAll();

	for (const auto& point1 : list1) {
		for (const auto& point2 : list2) {

			bool collision = Collision::isColliding(point1, point2, lab.walls, CollisionTestType::FULL_CHECK);

			if (!collision) {
				createRoute(point1, point2, lab.routes);
				lab.addHelperLine(point1, point2, WallType::LVL2);
			}
			else {
				lab.addHelperLine(point1, point2, WallType::LVL2DENIED);
			}
		}
	}
}

void WayPoint::createRoute(const Vector2& wp1, const Vector2& wp2, ConnectedNetwork& routes) {
	if (wp1 != wp2) {
		routes[wp1].push_back(wp2);
		routes[wp2].push_back(wp1);
	}
}

ConnectedNetwork WayPoint::connectPointsToNetwork(const std::vector<Vector2>& points, const ConnectedNetwork& routeNetwork, Labyrinth& lab) {
	// copy network that contains all routes besides the new points
	ConnectedNetwork routes = routeNetwork;

	// connect points to each other
	for (size_t i = 0; i < points.size(); i++) {
		for (size_t j = 0; j < points.size(); j++) {
			if (i != j) {
				const Vector2& p1 = points[i];
				const Vector2& p2 = points[j];

				// proper collision check
				if (!Collision::isColliding(p1, p2, lab.walls, CollisionTestType::FULL_CHECK)) {
					createRoute(p1, p2, routes);
					lab.addHelperLine(p1, p2, WallType::ADDITIONAL);
				}
				else {
					lab.addHelperLine(p1, p2, WallType::ADDITIONALDENIED);
				}
			}
		}
	}



	// connect points to network
	for (const auto& point : points) {
		for (size_t i = 0; i < lab.waypoints.size(); i++) {
			const auto& wp = lab.waypoints[i];
			
			// fast collision check with main-point of waypoint
			if (!Collision::isColliding(wp.main, point, lab.walls, CollisionTestType::VISIBILITY)) {
				for (const auto& point2 : wp.getAll()) {

					// proper collision check with all points of waypoint that may be reachable
					if (!Collision::isColliding(point, point2, lab.walls, CollisionTestType::FULL_CHECK)) {
						createRoute(point, point2, routes);
						lab.addHelperLine(point, point2, WallType::ADDITIONAL);
					}
					else {
						lab.addHelperLine(point, point2, WallType::ADDITIONALDENIED);
					}
				}
			}
		}
	}
	return routes;
}

