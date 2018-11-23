#pragma once

#include "Vector2.h"
#include <cmath> 

class Quad {
public:

	Quad(Vector2 point1, Vector2 point2, double width) {
		
		Vector3 rv = Vector3::getRichtungsVector(point1, point2);
		rv.rotateAroundZ(90);
		rv.normalize(width);

		p11 = point1 + rv;
		p12 = point1 - rv;
		p21 = point2 + rv;
		p22 = point2 - rv;
	}

Vector3 p11;
Vector3 p12;
Vector3 p21;
Vector3 p22;

};
