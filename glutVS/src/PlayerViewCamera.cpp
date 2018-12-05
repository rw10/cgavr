

#include "PlayerViewCamera.h"
#include "Model.h"

PlayerViewCamera::PlayerViewCamera(std::shared_ptr<Player> player) : player(player), fixedPlayer(true)
{}

PlayerViewCamera::PlayerViewCamera() : fixedPlayer(false)
{}

void PlayerViewCamera::update() {
	const std::shared_ptr<Player>& p = fixedPlayer? player : Model::get().getPlayer();
		
	position = p->position;
	lookingDirection = p->lookingDirection;
	FirstPersonCamera::update();
}