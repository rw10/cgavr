/*
 * Labyrinth.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */



#include "Labyrinth.h"

#include <iostream>
#include <algorithm>
#include <cmath> 

#include "TextureLoader.h"
#include "ViewSettings.h"
#include "GlutWindow.h"
#include "Collision.h"

Labyrinth::Labyrinth() {
	lowCorner = Vector2(0, 0);
	highCorner = Vector2(0, 0);
}

Labyrinth::~Labyrinth() {}

void Labyrinth::addWall(const Wall& wall){
	// add drawable wall
	walls.push_back(wall);
	
	// add points whereever the wall intersects with another wall
	Collision::addConnections(wall, corners);

	// add a cylinder to make the corners round
	createRoundCorner(wall.begin);
	createRoundCorner(wall.end);

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

void Labyrinth::addWall(const Vector2& begin, const Vector2& end) {
	addWall(Wall(begin, end, TextureLoader::get().wallTexture));
}

void Labyrinth::addHelperLine(const Vector3& begin, const Vector3& end, WallType type) {
	const ViewSettings& vs = GlutWindow::get().getViewSettings();
	switch (type) {
	case WallType::ADDITIONAL:
		additionalRouteWalls.push_back(Wall(begin, end, vs.additionalRouteWalls.color));
		break;
	case WallType::ADDITIONALDENIED:
		additionalDeniedRouteWalls.push_back(Wall(begin, end, vs.additionalDeniedRouteWalls.color));
		break;
	case WallType::AUTO:
		autoRouteWalls.push_back(Wall(begin, end, vs.autoRouteWalls.color));
		break;
	case WallType::DIJKSTRA:
		dijkstraRoute.push_back(Wall(begin, end, vs.dijkstraRoute.color));
		break;
	case WallType::LVL1:
		lvl1RouteWalls.push_back(Wall(begin, end, vs.lvl1RouteWalls.color));
		break;
	case WallType::LVL1DENIED:
		lvl1DeniedRouteWalls.push_back(Wall(begin, end, vs.lvl1DeniedRouteWalls.color));
		break;
	case WallType::LVL2:
		lvl2RouteWalls.push_back(Wall(begin, end, vs.lvl2RouteWalls.color));
		break;
	case WallType::LVL2DENIED:
		lvl2DeniedRouteWalls.push_back(Wall(begin, end, vs.lvl2DeniedRouteWalls.color));
		break;
	case WallType::MAINWAYPOINT:
		wayPointWalls.push_back(Wall(begin, end, vs.wayPointWalls.color));
		break;
	case WallType::WAYPOINT:
		wayPointWalls.push_back(Wall(begin, end, vs.wayPointWalls.color * 2));
		break;
	default:
		break;
	}
}

void Labyrinth::show(const double time, const ViewSettings& viewSettings)
{

	// TODO: make Floor an own class
	// draw the floor
	draw();

	// draw the walls
	for (auto& wall : walls) {
		wall.animate(time);
	}

	// draw the "round corners"
	for (auto& corner : roundCorners) {
		corner.second.animate(time);
	}

	// draw auxiliary walls
	if (viewSettings.wayPointWalls.show) {
		for (auto& wall : wayPointWalls) {
			wall.animate(time);
		}
	}
	if (viewSettings.autoRouteWalls.show) {
		for (auto& wall : autoRouteWalls) {
			wall.animate(time);
		}
	}
	if (viewSettings.lvl1RouteWalls.show) {
		for (auto& wall : lvl1RouteWalls) {
			wall.animate(time);
		}
	}
	if (viewSettings.lvl1DeniedRouteWalls.show) {
		for (auto& wall : lvl1DeniedRouteWalls) {
			wall.animate(time);
		}
	}
	if (viewSettings.lvl2RouteWalls.show) {
		for (auto& wall : lvl2RouteWalls) {
			wall.animate(time);
		}
	}
	if (viewSettings.lvl2DeniedRouteWalls.show) {
		for (auto& wall : lvl2DeniedRouteWalls) {
			wall.animate(time);
		}
	}
	if (viewSettings.additionalRouteWalls.show) {
		for (auto& wall : additionalRouteWalls) {
			wall.animate(time);
		}
	}
	if (viewSettings.additionalDeniedRouteWalls.show) {
		for (auto& wall : additionalDeniedRouteWalls) {
			wall.animate(time);
		}
	}
	if (viewSettings.dijkstraRoute.show) {
		for (auto& wall : dijkstraRoute) {
			wall.animate(time);
		}
	}
}


void Labyrinth::animate(const double ) {
	draw();
}

void Labyrinth::draw(void) const {

	// draw the floor

	// enable texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureLoader::get().groundTexture[0]);
	// use repeat mode for wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLfloat textureSizeX = (GLfloat)(highCorner.gl_x() / Settings::TextureSizeMultiplier);
	GLfloat textureSizeY = (GLfloat)(highCorner.gl_y() / Settings::TextureSizeMultiplier);

	// draw floor
	glBegin(GL_QUADS);
	glColor3b(50, 50, 50);		//grey

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

	
	// draw ceiling
	/*
	GLfloat height = (GLfloat) (highCorner.z + Settings::WallHeight);
	glVertex3f(lowCorner.gl_x(), lowCorner.gl_y(), height);
	glVertex3f(lowCorner.gl_x(), highCorner.gl_y(), height);
	glVertex3f(highCorner.gl_x(), highCorner.gl_y(), height);
	glVertex3f(highCorner.gl_x(), lowCorner.gl_y(), height);
	*/
	
	glEnd();
}



void Labyrinth::initRouting() {
	WayPoint::buildRoutingNetwork(*this);
}


Dijkstra Labyrinth::calculateRoute(const Vector2& start, const Vector2& end) {
	additionalRouteWalls.clear();
	additionalDeniedRouteWalls.clear();
	dijkstraRoute.clear();

	startPoint = start;
	endPoint = end;
	std::vector<Vector2> addPoints;
	addPoints.push_back(start);
	addPoints.push_back(end);

	ConnectedNetwork fullRoutes = WayPoint::connectPointsToNetwork(addPoints, routes, *this);
	Dijkstra dijkstra(fullRoutes, start, end);

	const ViewSettings& vs = GlutWindow::get().getViewSettings();

	// if dijkstra.route is empty, there is no connection between the points
	for (size_t i = 1; i < dijkstra.route.size(); i++) {
		const auto& pt1 = dijkstra.route[i - 1];
		const auto& pt2 = dijkstra.route[i];
		dijkstraRoute.push_back(Wall(pt1, pt2, vs.dijkstraRoute.color));
	}

	return dijkstra;
}



void Labyrinth::createRoundCorner(const Vector2& corner) {
	// create the drawable object
	if (roundCorners.count(corner) == 0) {
		roundCorners[corner] = Cylinder(corner, Settings::WallWidth, Settings::WallHeight, TextureLoader::get().wallTexture);
	}

	const auto& connectedCorners = corners[corner];
	const size_t size = connectedCorners.size();

	if (size == 1) {
		// = end of a line
		// put 2 waypoint with 45° on opposite side
		Vector2 direction = connectedCorners[0] - corner;

		int angle = (int) round(450 - Vector3::calcAngleInXY(direction, Vector3(1, 0, 0)));
		roundCorners[corner].setStartAngle(angle);
		roundCorners[corner].setEndAngle(angle + 180);
	}
	else if (size == 2) {
		// find the angle greater than 180° and put waypoints on that side
		// angle = half the given angle, dist = Constants::PlayerRadius

		Vector2 direction1 = connectedCorners[0] - corner;
		Vector2 direction2 = connectedCorners[1] - corner;

		int angle = (int)round(450 - Vector3::calcAngleInXY(direction1, Vector3(1, 0, 0)));
		double angle2 = Vector3::calcAngleInXY(direction1, direction2);

		bool left = angle2 < 180;
		if (left) {
			angle = (int)round(450 - Vector3::calcAngleInXY(direction2, Vector3(1, 0, 0)));
			angle2 = round(360 - angle2);
		}

		roundCorners[corner].setStartAngle(angle);
		roundCorners[corner].setEndAngle(angle + (int) angle2 - 180);
	}
	else {
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

				int angle = (int)round(450 - Vector3::calcAngleInXY(direction1, Vector3(1, 0, 0)));
				int angle2 = (int) angles[0] - 180;

				roundCorners[corner].setStartAngle(angle);
				roundCorners[corner].setEndAngle(angle + angle2);
			}
		}
		if (!found) {
			// no round corner needed -> remove the drawable
			roundCorners.erase(corner);
		}
	}
}