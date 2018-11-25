#pragma once

#include "ViewSettings.h"

class Drawable {
public:

	// viewSettings are only for hiding elements
	// usually not needed
	virtual void show(const double time, const ViewSettings& ) {
		animate(time);
	}

	virtual void animate(const double time) = 0;

protected:
	virtual void draw(void) const = 0;
};