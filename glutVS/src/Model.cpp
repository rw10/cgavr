#include "Model.h"
#include "LabyrinthBuilder.h"

std::vector<Model> Model::INSTANCES = std::vector<Model>();
std::mutex Model::dataMutex;

Model::Model() : initialized(false)
{
	
	// add labyrinth
	setLab(LabyrinthBuilder::build());

	// set start/end
	setStart(45, 5);
	setEnd(95, 55);

	// find route
	calculateRoute();
	
	   
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

void Model::setLab(std::shared_ptr<Labyrinth> labyrinth) {
	lab = labyrinth;
}

void Model::setStart(double x, double y) {
	start = Vector2(x, y);

	// add a drawable object
	begin = std::shared_ptr<Cylinder>(
		new Cylinder(
			start,
			Settings::PlayerRadius,
			Settings::PlayerHeight,
			Color3ub(255, 0, 0)		// red
		)
	);
}

void Model::setEnd(double x, double y) {
	end = Vector2(x, y);

	// add a drawable object
	finish = std::shared_ptr<Cylinder>(
		new Cylinder(
			end,
			Settings::PlayerRadius,
			Settings::PlayerHeight,
			Color3ub(212, 175, 55)		// gold
		)
	);
}

void Model::calculateRoute() {
	// find route
	Dijkstra dijkstra = lab->calculateRoute(
		start,
		end
	);
	route = dijkstra.route;

	if (route.size() > 1) {
		player = std::shared_ptr<Player>(new Player(route));
	}

	rebuildDrawables();
}


void Model::update() {
	if (initialized) {
		player->update();
	}
}

void Model::rebuildDrawables() {
	dataMutex.lock();
	drawables.clear();
	drawables.push_back(lab);
	drawables.push_back(begin);
	drawables.push_back(finish);

	initialized = (route.size() > 1);
	if (initialized) {
		drawables.push_back(player);
	}

	dataMutex.unlock();
}

void Model::show(const double time, const ViewSettings& vs) {
	dataMutex.lock();
	for (const auto& drawable : drawables) {
		drawable->show(time, vs);
	}
	dataMutex.unlock();
}