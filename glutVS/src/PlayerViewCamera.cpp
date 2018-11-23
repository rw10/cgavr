#include "pch.h"

#include "PlayerViewCamera.h"

PlayerViewCamera::PlayerViewCamera(std::shared_ptr<Player> player) : player(player)
{}

void PlayerViewCamera::update() {
	position = player->position;
	lookingDirection = player->lookingDirection;
	FirstPersonCamera::update();
}