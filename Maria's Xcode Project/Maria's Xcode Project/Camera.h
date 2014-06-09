#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"

class Camera
{
public:
	// Constructor
	Camera();
	~Camera() {}

	// Getters / Setters
	void setPosition(Vector3f pos);
	void setFreeLook();
	void setTopDown();
	//For physics - Launching the ball
	Vector3f getViewDir(){ return viewDir; };

	// Tick
	void render();

	// Functions
	void move(Vector3f direction);
	void moveForwards(float distance);
	void moveUp(float distance);
	void strafeRight(float distance);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void rotateXYZ(Vector3f angles);
private:
	// Member Variables
	Vector3f position, viewDir;
	float rotatedX, rotatedY, rotatedZ;
	bool viewDirChanged;

	// Private Functions
	void getViewDirection();
};

#endif /*CAMERA_H*/