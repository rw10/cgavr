#include "pch.h"

#include "LabyrinthBuilder.h"
#include "Textures.h"
#include "Color3ub.h"
#include "Constants.h"
#include <cmath>


std::shared_ptr<Labyrinth> LabyrinthBuilder::build() {

	// create labyrinth
	std::shared_ptr<Labyrinth> lab(new Labyrinth);

	// add walls
	boundaries(lab, 100);
	   
	staticLab(lab);

	//star(lab, 8, 8, 20, Vector2(0,0));
	//star(lab, 8, 4, 20, Vector2(50, 0));
	//star(lab, 8, 8, 20, Vector2(50, 50));
	//star(lab, 8, 8, 20, Vector2(0, 50));

	// trigger building the routes
	lab->initRouting();

	return lab;
}


void LabyrinthBuilder::someWalls(std::shared_ptr<Labyrinth> lab) {
	// some walls
	double width = 0;
	for (int i = 0; i < 10; i++) {
		Wall wall(
			Vector2(i * 10, 5 * (i % 3)),
			Vector2(i * 10 + 20, 50 + 5 * (i % 3)),
			Color3ub(125, 10, 23),
			width
		);
		lab->addWall(wall);
	}
}

void LabyrinthBuilder::sawtooth(std::shared_ptr<Labyrinth> lab) {
	// sägezahn muster
	for (int i = 0; i < 3; i++) {
		lab->addWall(Vector2(10 * i, 0 * i), Vector2(10 * i, 10 * (i + 1)));
		lab->addWall(Vector2(10 * i, 10 * (i + 1)), Vector2(10 * (i + 1), 0 * (i + 1)));
	}
}

void LabyrinthBuilder::star(std::shared_ptr<Labyrinth> lab, size_t parts, size_t points, double size, Vector2 offset) {
	using namespace Constants;

	size_t limit = (size_t)fmin(parts, points);

	for (int i = 0; i < limit; i++) {
		lab->addWall(
			Wall(
				Vector2(offset.x, offset.y),
				Vector2(offset.x + size * cos(2 * PI * i / parts), offset.y + size * sin(2 * PI * i / parts)),
				Textures::get().wallTexture
			)
		);
	}
}


void LabyrinthBuilder::boundaries(std::shared_ptr<Labyrinth> lab, double size) {
	Vector2 bl(0, 0);
	Vector2 tl(size, 0);
	Vector2 br(0, size);
	Vector2 tr(size, size);

	lab->addWall(bl, br);
	lab->addWall(br, tr);
	lab->addWall(tr, tl);
	lab->addWall(tl, bl);
}

void LabyrinthBuilder::staticLab(std::shared_ptr<Labyrinth> lab) {
	// built after sample_lab.png

	lab->addWall(
		Vector2(10,10),
		Vector2(10, 50)
	);
	lab->addWall(
		Vector2(10, 50),
		Vector2(10, 90)
	);
	lab->addWall(
		Vector2(10, 90),
		Vector2(40, 90)
	);
	lab->addWall(
		Vector2(10, 50),
		Vector2(20, 50)
	);
	lab->addWall(
		Vector2(10, 10),
		Vector2(50, 10)
	);
	lab->addWall(
		Vector2(50, 10),
		Vector2(80, 10)
	);
	lab->addWall(
		Vector2(20, 50),
		Vector2(20, 20)
	);
	lab->addWall(
		Vector2(20, 20),
		Vector2(40, 20)
	);
	lab->addWall(
		Vector2(20, 60),
		Vector2(20, 80)
	);
	lab->addWall(
		Vector2(20, 80),
		Vector2(50, 80)
	);
	lab->addWall(
		Vector2(50, 80),
		Vector2(80, 80)
	);
	lab->addWall(
		Vector2(50, 0),
		Vector2(50, 10)
	);
	lab->addWall(
		Vector2(50, 100),
		Vector2(50, 80)
	);
	lab->addWall(
		Vector2(50, 80),
		Vector2(50, 70)
	);
	lab->addWall(
		Vector2(50, 70),
		Vector2(30, 70)
	);
	lab->addWall(
		Vector2(30, 70),
		Vector2(30, 30)
	);
	lab->addWall(
		Vector2(30, 30),
		Vector2(50, 30)
	);
	lab->addWall(
		Vector2(50, 30),
		Vector2(50, 20)
	);
	lab->addWall(
		Vector2(50, 20),
		Vector2(80, 20)
	);
	lab->addWall(
		Vector2(80, 20),
		Vector2(80, 40)
	);
	lab->addWall(
		Vector2(40, 40),
		Vector2(40, 60)
	);
	lab->addWall(
		Vector2(40, 40),
		Vector2(60, 40)
	);
	lab->addWall(
		Vector2(40, 60),
		Vector2(60, 60)
	);
	lab->addWall(
		Vector2(60, 40),
		Vector2(60, 50)
	);
	lab->addWall(
		Vector2(60, 60),
		Vector2(60, 50)
	);
	lab->addWall(
		Vector2(60, 50),
		Vector2(70, 50)
	);
	lab->addWall(
		Vector2(60, 90),
		Vector2(90, 90)
	);
	lab->addWall(
		Vector2(90, 90),
		Vector2(90, 50)
	);
	lab->addWall(
		Vector2(90, 50),
		Vector2(70, 50)
	);
	lab->addWall(
		Vector2(70, 50),
		Vector2(60, 50)
	);
	lab->addWall(
		Vector2(70, 50),
		Vector2(70, 30)
	);
	lab->addWall(
		Vector2(70, 50),
		Vector2(70, 70)
	);
	lab->addWall(
		Vector2(90, 50),
		Vector2(90, 10)
	);
	lab->addWall(
		Vector2(90, 50),
		Vector2(100, 50)
	);
	lab->addWall(
		Vector2(80, 80),
		Vector2(80, 60)
	);
	lab->addWall(
		Vector2(70, 70),
		Vector2(60, 70)
	);
	lab->addWall(
		Vector2(70, 30),
		Vector2(60, 30)
	);


	//triangle90(lab, 10, 0, Vector2(80, 40));
	//triangle90(lab, 10, 180, Vector2(80, 60));


}


void LabyrinthBuilder::triangle90(std::shared_ptr<Labyrinth> lab, double size, double rotation, Vector2 offset) {

	Vector2 A(0, 0);
	Vector2 B(0, size);
	Vector2 C(size, 0);

	if (rotation != 0) {
		B.rotateAroundZ(rotation);
		C.rotateAroundZ(rotation);
	}

	A = Vector2(A + offset);
	B = Vector2(B + offset);
	C = Vector2(C + offset);

	lab->addWall(A, B);
	lab->addWall(A, C);
	lab->addWall(B, C);


}
