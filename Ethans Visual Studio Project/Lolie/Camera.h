#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"

class Camera
{
public:
	Camera();
	~Camera() {}

	void setPosition(Vector3f pos);
	void setFreeLook();
	void setTopDown();

	void render();
	void move(Vector3f direction);
	void moveForwards(float distance);
	void moveUp(float distance);
	void strafeRight(float distance);

	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void rotateXYZ(Vector3f angles);

private:
	Vector3f position;
	Vector3f viewDir;
	float rotatedX, rotatedY, rotatedZ;
	bool viewDirChanged;

	void getViewDirection();
};

#endif /*CAMERA_H*/