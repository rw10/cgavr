#pragma once

#include <memory>
#include "Labyrinth.h"

class LabyrinthBuilder {
public:
	static std::shared_ptr<Labyrinth> build();

private:
	static void sawtooth(std::shared_ptr<Labyrinth> lab);
	static void triangle90(std::shared_ptr<Labyrinth> lab, double size, double rotation, Vector2 offset);
	static void someWalls(std::shared_ptr<Labyrinth> lab);
	static void star(std::shared_ptr<Labyrinth> lab, size_t parts, size_t points, double size, Vector2 offset);
	static void boundaries(std::shared_ptr<Labyrinth> lab, double size);
	static void staticLab(std::shared_ptr<Labyrinth> lab);
	// ... more

	
	// static methods only -> no constructor
	LabyrinthBuilder(){}
	~LabyrinthBuilder(){}

};