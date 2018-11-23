#pragma once

#include "Drawable.h"
#include "Updatable.h"

#include <vector>
#include <memory>
#include "Vector2.h"
#include "ConeTop.h"

class Player : public Drawable, public Updatable
{
public:

	Player(const std::vector<Vector2>& route);
	~Player() {}

	virtual void update();

	// TODO: change speed by using sin(time) -> creates a more natural, unsteady movement
	double speed;
	Vector3 movement;

	int currentRouteIndex;
	std::vector<Vector2> route;

	Vector3 position;
	Vector3 lookingDirection;

protected:
	virtual void paint(double time);
	virtual void draw(void) const;

private:
	std::shared_ptr<ConeTop> cone;
	std::vector<std::shared_ptr<Drawable> > parts;

	void setForNextTarget();
	void lerpLookingDirection();

};