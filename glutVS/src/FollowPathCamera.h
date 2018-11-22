#pragma once

#include "FirstPersonCamera.h"
#include <vector>
#include "Vector2.h"

class FollowPathCamera : public FirstPersonCamera {
public:
	FollowPathCamera(const std::vector<Vector2>& route);
	~FollowPathCamera() {}

	virtual void update();

	// TODO: change speed by using sin(time) -> creates a more natural, unsteady movement
	double speed;
	Vector3 movement;

	int currentPosition;
	std::vector<Vector2> route;


private:
	void setForNextTarget();

	void lerpLookingDirection();
};
