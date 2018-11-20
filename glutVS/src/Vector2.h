#pragma once

#include "Vector3.h"
#include <math.h>

class Vector2 : public Vector3
{
public:
	Vector2() : Vector3() {}
	Vector2(const Vector3& vec) : Vector3(vec) {}
	Vector2(double x, double y) : Vector3(x, y, 0){}
	~Vector2(){}

	using Vector3::operator*;
	using Vector3::operator+;
	using Vector3::operator-;

	// sort by x, then by y value
	// has to exist in order to use as key in map
	bool operator< (const Vector2& other) const {
		return x == other.x ?
			y < other.y :
			x < other.x;
	}

	bool operator== (const Vector2& other) const {
		return x == other.x && y == other.y;
	}

	// a vector3 will be flattened on the z value
	Vector2 operator= (const Vector3& vector3) const
	{
		return Vector2(
			vector3.x, vector3.y
		);
	}


	static Vector2 getClosestPointOnLineSegment(const Vector2& A, const Vector2& B, const Vector2& P)
	{
		Vector2 AP = P - A;       //A->P
		Vector2 AB = B - A;       //A->B

		// if A and B are the same point, return one of them
		if (AB.getLength() == 0) {
			return A;
		}
			
		//normalized distance to closest point 
		double distance = dotProduct(AP, AB) / pow(AB.getLength(), 2); 

		if (distance < 0){
			return A;
		} else if (distance > 1){
			return B;
		} else{
			return A + AB * distance;
		}
	}

};