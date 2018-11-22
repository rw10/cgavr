#include "pch.h"

#include "Axis.h"
#include "Settings.h"

Axis::Axis() {
	double axisWidth = 1;

	// x axis
	axis.push_back(
		Block::createByCorners(
			Vector3(0, 0, 0),
			Vector3(100, axisWidth, axisWidth),
			Color3ub(255, 0, 0)
		)
	);

	// y axis
	axis.push_back(
		Block::createByCorners(
			Vector3(0, 0, 0),
			Vector3(axisWidth, 100, axisWidth),
			Color3ub(0, 255, 0)
		)
	);

	// z axis
	axis.push_back(
		Block::createByCorners(
			Vector3(0, 0, 0),
			Vector3(axisWidth, axisWidth, 100),
			Color3ub(0, 0, 255)
		)
	);
}

Axis::~Axis(){}

void Axis::draw(void) const {
	if (Settings::ShowAxis){
		for (const auto& a : axis) {
			a.draw();
		}
	}
}