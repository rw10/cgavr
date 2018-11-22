#include "pch.h"
#include "Dijkstra.h"

#include <algorithm>

Dijkstra::Dijkstra(const ConnectedNetwork& routes, Vector2 start, Vector2 target) : routes(routes)
{
	// init
	std::shared_ptr<DijkstraPoint> startNode = std::shared_ptr<DijkstraPoint>(new DijkstraPoint(start));
	visited.emplace(start);	
	addNextTargets(startNode);
	bool finished = false;

	// search target
	while (queue.size() != 0 && !finished) {
		// get the first element from queue
		auto closest = queue[0];
		if (closest->position == target) {
			finished = true;
			// assemble route by going backwards
			assemble(closest);
		}
		else {
			// mark as visited
			visited.emplace(closest->position);
			// remove it from queue
			queue.erase(queue.begin());
			// add connected points as targets
			addNextTargets(closest);
		}
	}
}

void Dijkstra::addNextTargets(std::shared_ptr<DijkstraPoint> currentPoint) {
	const auto& targets = routes[currentPoint->position];
	for (const auto& target : targets) {
		
		// only unvisited
		if (visited.count(target) == 0) {			
			// add to queue
			queue.push_back(std::shared_ptr<DijkstraPoint>(new DijkstraPoint(target, currentPoint)));
		}
	}
	// remove already visited and sort
	updateQueue();
}

void Dijkstra::updateQueue() {
	// remove visited
	auto it = queue.begin();
	while (it != queue.end()) {
		auto& i = *it;
		if (visited.count(i->position) != 0) {
			it = queue.erase(it);
		}
		else {
			it++;
		}
	}

	// sort by distance
	std::sort(queue.begin(), queue.end(), sortByDistance);
}

void Dijkstra::assemble(std::shared_ptr<DijkstraPoint> target) {
	route.push_back(Vector2(target->position));

	if (!target->isFirst()) {
		assemble(target->predecessor);
	}
}