#include "pch.h"

#include "FollowPathCamera.h"
#include "Settings.h"
#include <cmath>


FollowPathCamera::FollowPathCamera(const std::vector<Vector2>& route) : route(route)
{
	// set speed
	speed = Settings::PlayerSpeed;

	// set height over ground
	for (auto& pt : this->route) {
		pt.z = fmax(pt.z, Settings::PlayerHeight);
	}

	// init the route
	currentPosition = -1;
	setForNextTarget();

	// look at first target
	lookingDirection = movement;
}

void FollowPathCamera::update() {
	if (currentPosition < route.size() - 1) {
		const Vector2& next = route[currentPosition + 1];
		double distanceLeft = (next - position).getLengthXY();

		lerpLookingDirection();

		// update to follow next part of the route
		if (speed >= distanceLeft) {
			setForNextTarget();
		}
		else {
			position = position + movement;
		}
	}
	FirstPersonCamera::update();
}

void FollowPathCamera::setForNextTarget() {
	currentPosition++;
	position = route[currentPosition];

	if (currentPosition < route.size() - 1) {
		const Vector2& last = route[currentPosition];
		const Vector2& next = route[currentPosition + 1];

		movement = next - last;
		movement.normalize(speed);
	}
	else {
		// reset on arrival...
		currentPosition = -1;
		setForNextTarget();
	}

}


void FollowPathCamera::lerpLookingDirection() {
	// slowly change the looking direction
	double turnSpeed = 0.04;
	lookingDirection = lookingDirection * (1 - turnSpeed) + (movement - lookingDirection) * turnSpeed;
}