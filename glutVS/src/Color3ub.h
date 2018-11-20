#pragma once
class Color3ub
{
public:
	Color3ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	~Color3ub();

	Color3ub operator*(const double& multiplier) const;

	unsigned char r, g, b, a;
private:
	Color3ub();
};
