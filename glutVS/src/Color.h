#pragma once
class Color
{
public:
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	~Color();

	unsigned char r, g, b, a;
private:
	Color();
};

