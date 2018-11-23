#pragma once

#include "Updatable.h"

#include <vector>
#include <memory>
#include "Labyrinth.h"
#include "Player.h"
#include "Cylinder.h"
#include "Vector2.h"

class Model : public Updatable
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

	const std::shared_ptr<Player> getPlayer() const {
		return player;
	}

	virtual void update();

private:
	Model();

	std::shared_ptr<Player> player;
	std::shared_ptr<Cylinder> finish;

	// list of all drawable objects
	std::vector<std::shared_ptr<Drawable> > drawables;

	std::shared_ptr<Labyrinth> lab;
	std::vector<Vector2> route;

	static std::vector<Model> INSTANCES;

};
