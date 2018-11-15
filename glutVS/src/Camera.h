#pragma once

#include "Vector3.h"

class Camera
{
public:
	Camera();
	~Camera();

	Vector3 position;
	Vector3 lookAtPoint;
	Vector3 upDirection;

	virtual void update();

	virtual void rotateAroundX(double degrees) = 0;
	virtual void rotateAroundY(double degrees) = 0;
	virtual void rotateAroundZ(double degrees) = 0;

	/**
	* move the camera position in x-y
	* degrees = angle relative to looking direction
	* 0 = move forward
	* 90 = strafe right
	* ...
	* inversion by negative distance is also possible
	*/
	void move(double distance, double degrees);

	/**
	* move the camera in z
	* moveDown => negative value param
	*/
	void moveUp(double distance);

};

