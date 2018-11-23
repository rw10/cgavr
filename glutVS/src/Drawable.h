#pragma once


class Drawable {
public:
	virtual void paint(double) = 0;

protected:
	virtual void draw(void) const = 0;
};