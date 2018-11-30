#include "pch.h"

#include "Player.h"
#include "Settings.h"
#include "Constants.h"
#include <cmath>
#include "TextureLoader.h"
#include "ConeTop.h"


Player::Player(const std::vector<Vector2>& dijkstraRoute)		// : route(route)
{
	// duplicate start and finish with altered height
	route.push_back(dijkstraRoute[0]);
	route.insert(route.end(), dijkstraRoute.begin(), dijkstraRoute.end());
	route.push_back(dijkstraRoute[dijkstraRoute.size()-1]);

	for (auto& r : route) {
		r.z = Settings::PlayerHeight;
	}
	route[0].z = Settings::WallHeight + Settings::PlayerHeight;
	route[route.size()-1].z = Settings::WallHeight + Settings::PlayerHeight;

	// set speed
	speed = Settings::PlayerSpeed;

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
			//TextureLoader::get().playerTexture
			TextureLoader::get().arrowTexture
		)
	);
	parts.push_back(cone);
}

void Player::update() {

	move();

	// lerp the looking direction to fit movement direction
	lerpLookingDirection();

	updateModel();
}

void Player::move() {

	double distanceToGo = Settings::PlayerSpeed;

	int nextRouteIndex;
	do {
		// calc movement
		nextRouteIndex = (currentRouteIndex + 1) % route.size();
		const Vector2& next = route[nextRouteIndex];
		const Vector2& last = route[currentRouteIndex];
		movement = next - last;
		movement.normalize(distanceToGo);

		// calculate if the movement step is enough to reach the next point
		double distanceToNextPoint = (next - position).getLength();	//.getLengthXY();
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
}

void Player::updateModel() {
	// rotate the model to face in the direction the player looks...
	double angle = 360 - Vector3::calcAngleInXY(lookingDirection, Constants::yUp);
	cone->rotation.z = angle;
	cone->rotationCenter = position;

	// update the position of the player model
	cone->pos = position;
	cone->pos.z -= Settings::PlayerHeight;
}

void Player::setForNextTarget() {
	currentRouteIndex++;
	// reset on arrival
	currentRouteIndex %= route.size();
	position = route[currentRouteIndex];
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
