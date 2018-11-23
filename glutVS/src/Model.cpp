
#include "pch.h"

#include "Model.h"
#include "LabyrinthBuilder.h"


std::vector<Model> Model::INSTANCES = std::vector<Model>();

Model::Model()
{
	// add labyrinth
	lab = LabyrinthBuilder::build();
	drawables.push_back(lab);

	// find route
	Dijkstra dijkstra = lab->calculateRoute(
		Vector2(45, 5),
		Vector2(95, 55)
	);
	route = dijkstra.route;

	player = std::shared_ptr<Player>(new Player(route));
	drawables.push_back(player);

	Vector2 end = *route.rbegin();
	finish = std::shared_ptr<Cylinder>(
		new Cylinder(
			end,			// last position of route
			Settings::PlayerRadius,
			Settings::PlayerHeight,
			Color3ub(212, 175, 55)		// gold
		)
	);
	drawables.push_back(finish);


	/*
	if (dijkstra.route.size() != 0) {
		route.reserve(1 + dijkstra.route.size()); // preallocate memory

		auto onTop = dijkstra.route[0];
		onTop.z = 100;
		route.push_back(onTop);
		route.insert(route.end(), dijkstra.route.begin(), dijkstra.route.end());
	}
	*/


	// 3D Objects
	//std::shared_ptr<ConeTop> c(new ConeTop(Vector3(0,0,0), 6, 30, Textures::get().wallTexture));
	//drawables.push_back(c);

	// 3D Histogram
	//std::shared_ptr<Histogram3D> hist(new Histogram3D);
	//drawables.push_back(hist);

}

Model::~Model()
{
}


void Model::update(double time) {
	player->update(time);
}
