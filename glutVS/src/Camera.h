#pragma once

#include "Vector3.h"

enum CameraType {
	LOOK_AT, FIRST_PERSON
};


class Camera
{
public:
	Camera();
	~Camera();

	Vector3 position;
	Vector3 lookAtPoint;
	Vector3 upDirection;

	CameraType type;

	void rotateAroundX(double degrees);
	void rotateAroundY(double degrees);
	void rotateAroundZ(double degrees);

	/**
	* degrees = angle relative to looking direction
	* 0 = move forward
	* 90 = strafe right
	* ...
	* inversion by negative distance is also possible
	*/
	void move(double distance, double degrees);

	// moveDown = negative value param
	void moveUp(double distance);

	// turn left = negative value param
	virtual void turnRight(double degrees) = 0;

	// turn down = negative value param
	virtual void turnUp(double degrees) = 0;

	void update();

private:

};

