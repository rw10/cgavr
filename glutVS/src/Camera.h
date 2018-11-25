#pragma once

#include "Vector3.h"
#include "Vector2.h"

class Camera
{
public:
	Camera();
	~Camera();

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
	virtual void move(double distance, double degrees);
	 
	/**
	* move the camera in z
	* moveDown => negative value param
	*/
	void moveUp(double distance);

	virtual void moveToPoint3D(const Vector3& point);
	virtual void moveToPoint2D(const Vector3& point);

	const Vector3& getPosition() const { return position; }
	const Vector3& getLookAtPoint() const { return lookAtPoint; }

protected:
	Vector3 position;
	Vector3 lookAtPoint;
	Vector3 upDirection;

	// auxiliary function to update other things besides position, called during moveToPoint
	virtual void moveEnvironment(const Vector3&){}

	virtual void initPerspective(void) = 0;

};

