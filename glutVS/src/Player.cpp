#include "pch.h"

#include "Player.h"
#include "Settings.h"
#include <cmath>
#include "TextureLoader.h"
#include "ConeTop.h"


Player::Player(const std::vector<Vector2>& route) : route(route)
{
	// set speed
	speed = Settings::PlayerSpeed;

	// set height over ground
	for (auto& pt : this->route) {
		pt.z = fmax(pt.z, Settings::PlayerHeight);
	}

	// init the route
	currentRouteIndex = -1;
	setForNextTarget();

	// look at first target
	lookingDirection = movement;

	// create 3D model
	cone = std::shared_ptr<ConeTop>(
		new ConeTop(
			Vector2(position), 
			Settings::PlayerRadius, 
			Settings::PlayerHeight, 
			TextureLoader::get().playerTexture
		)
	);
	parts.push_back(cone);
}

void Player::update(double time) {
	if (currentRouteIndex < route.size() - 1) {
		const Vector2& next = route[currentRouteIndex + 1];

		// if speed value has changed, update the movement vector
		if (speed != Settings::PlayerSpeed) {
			speed = Settings::PlayerSpeed;
			const Vector2& last = route[currentRouteIndex];
			movement = next - last;
			movement.normalize(speed);
		}

		double distanceLeft = (next - position).getLengthXY();

		lerpLookingDirection();

		// update to follow next part of the route
		if (speed >= distanceLeft) {
			setForNextTarget();
		}
		else {
			position = position + movement;
		}
		cone->pos = position;
		cone->pos.z = 0;
	}
}

void Player::setForNextTarget() {
	currentRouteIndex++;
	position = route[currentRouteIndex];

	if (currentRouteIndex < route.size() - 1) {
		const Vector2& last = route[currentRouteIndex];
		const Vector2& next = route[currentRouteIndex + 1];

		movement = next - last;
		movement.normalize(speed);
	}
	else {
		// reset on arrival...
		currentRouteIndex = -1;
		setForNextTarget();
	}
}


void Player::lerpLookingDirection() {
	// slowly change the looking direction
	double turnSpeed = 0.1 * speed;
	lookingDirection = lookingDirection * (1 - turnSpeed) + (movement - lookingDirection) * turnSpeed;
}

void Player::paint(double time) {
	for (const auto& part : parts) {
		part->paint(time);
	}
}

void Player::draw(void) const {
	// nothing to do here
	// player is created over parts
}