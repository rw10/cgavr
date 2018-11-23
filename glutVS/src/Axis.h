#pragma once

#include "Drawable.h"
#include <vector>
#include "Block.h"

class Axis : public Drawable {
public:
	Axis();
	~Axis();

	virtual void paint(double time);

protected:
	virtual void draw(void) const;


	std::vector<Block> axis;
};