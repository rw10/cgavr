#pragma once

#include "Types.h"

#include "DijkstraPoint.h"

#include <set>

class Dijkstra {
public:

	Dijkstra(const ConnectedNetwork& routes, Vector2 start, Vector2 target);

	// result
	std::vector<Vector2> route;
private:

	// remove visited Points from queue
	void updateQueue();
	void assemble(std::shared_ptr<DijkstraPoint> target);

	ConnectedNetwork routes;
	std::vector<std::shared_ptr<DijkstraPoint>> queue;
	std::set<Vector2> visited;

	void addNextTargets(std::shared_ptr<DijkstraPoint>);


	static bool sortByDistance(const std::shared_ptr<DijkstraPoint>& d1, const std::shared_ptr<DijkstraPoint>& d2)
	{
		return *d1 < *d2;
	}

};
