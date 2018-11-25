#pragma once

#include "Drawable.h"
#include <vector>
#include "Block.h"

class Axis : public Drawable {
public:
	Axis();
	~Axis();

	virtual void show(const double time, const ViewSettings& viewSettings);
	virtual void animate(const double time);

protected:
	virtual void draw(void) const;


	std::vector<Block> axis;
};