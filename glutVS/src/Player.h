#pragma once

#include <vector>
#include "Vector2.h"

class Player {
public:

	Player(const std::vector<Vector2>& route);
	~Player() {}

	virtual void update();

	// TODO: change speed by using sin(time) -> creates a more natural, unsteady movement
	double speed;
	Vector3 movement;

	int currentPosition;
	std::vector<Vector2> route;


private:
	void setForNextTarget();
	void lerpLookingDirection();

	Vector3 position;
	Vector3 lookingDirection;


};