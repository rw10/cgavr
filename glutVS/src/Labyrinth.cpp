/*
 * Labyrinth.cpp
 *
 *  Created on: 11.10.2018
 *      Author: rene
 */

#include "pch.h"

#include "Labyrinth.h"

#include <iostream>
#include <cmath> 

#include "Textures.h"

Labyrinth::Labyrinth() {
	lowCorner = Vector2(0, 0);
	highCorner = Vector2(0, 0);
}

Labyrinth::~Labyrinth() {}

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

void Labyrinth::draw(void) const
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	drawFloor();

	// TODO: draw start and end-point!!!

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
	if (Settings::additionalRouteWalls.show) {
		for (auto& wall : additionalRouteWalls) {
			wall.draw();
		}
	}
	if (Settings::additionalDeniedRouteWalls.show) {
		for (auto& wall : additionalDeniedRouteWalls) {
			wall.draw();
		}
	}
	if (Settings::dijkstraRoute.show) {
		for (auto& wall : dijkstraRoute) {
			wall.draw();
		}
	}
}

void Labyrinth::drawFloor() const {

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


	// if dijkstra.route is empty, there is no connection between the points
	for (size_t i = 1; i < dijkstra.route.size(); i++) {
		const auto& pt1 = dijkstra.route[i - 1];
		const auto& pt2 = dijkstra.route[i];
		dijkstraRoute.push_back(Wall(pt1, pt2, Settings::dijkstraRoute.color));
	}

	return dijkstra;
}
