#pragma once

#include <vector>
#include <memory>
#include "Labyrinth.h"
#include "Player.h"
#include "Vector2.h"

class Model
{
public:
	~Model();

	// singleton construction
	static Model& get() {
		if (INSTANCES.size() == 0) {
			INSTANCES.push_back(Model());
		}
		return INSTANCES[0];
	}

	const std::vector<std::shared_ptr<Drawable> >& getDrawables() const {
		return drawables;
	}

	const std::vector<Vector2>& getRoute() const {
		return route;
	}

private:
	Model();

	Player player;

	// list of all drawable objects
	std::vector<std::shared_ptr<Drawable> > drawables;

	std::shared_ptr<Labyrinth> lab;
	std::vector<Vector2> route;

	static std::vector<Model> INSTANCES;

};
