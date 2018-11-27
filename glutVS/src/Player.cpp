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

void Player::update() {
	if (currentRouteIndex < route.size() - 1) {
		double distanceToGo = Settings::PlayerSpeed;

		do {
			// calc movement
			const Vector2& next = route[currentRouteIndex + 1];
			const Vector2& last = route[currentRouteIndex];
			movement = next - last;
			movement.normalize(distanceToGo);

			// calculate if the movement step is enough to reach the next point
			double distanceToNextPoint = (next - position).getLengthXY();
			distanceToGo -= distanceToNextPoint;

			// if there is distanceToGo left, the next point was reached prematurely
			if (distanceToGo > 0) {
				// set next point of the route as target
				setForNextTarget();
			}
			else {
				// move towards target
				position = position + movement;
			}

		// move again, if distance left
		} while (distanceToGo > 0);

		// lerp the looking direction to fit movement direction
		lerpLookingDirection();

		// update the position of the player model
		cone->pos = position;
		cone->pos.z = 0;
	}
}

void Player::setForNextTarget() {
	currentRouteIndex++;
	position = route[currentRouteIndex];

	if (currentRouteIndex == route.size() - 1) {
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

void Player::animate(const double time) {
	for (const auto& part : parts) {
		part->animate(time);
	}
}

void Player::draw(void) const {
	// nothing to do here
	// player is created over parts
}