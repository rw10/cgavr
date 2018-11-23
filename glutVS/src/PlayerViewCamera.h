#pragma once

#include "FirstPersonCamera.h"
#include <vector>
#include <memory>
#include "Player.h"

class PlayerViewCamera : public FirstPersonCamera {
public:
	PlayerViewCamera(std::shared_ptr<Player> player);
	~PlayerViewCamera() {}

	virtual void update();

private:
	std::shared_ptr<Player> player;
};
