#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"
#include "Ball.h"

class Camera
{
public:
	Camera();
	~Camera() {}

	void update();

	void setPosition(Vector3f pos);
	void setFreeLook();
	void setTopDown();
	void setballCamera(Ball* ball);

	void render();
	void move(Vector3f direction);
	void moveForwards(float distance);
	void moveUp(float distance);
	void strafeRight(float distance);

	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	Vector3f getRotates();
	void rotateXYZ(Vector3f angles);
    
    //For physics - Launching the ball
    Vector3f getViewDir(){return viewDir;}
	Vector3f getPosition(){ return position; }

private:
	Vector3f position;
	Vector3f viewDir;
	float rotatedX, rotatedY, rotatedZ;
	bool viewDirChanged;

	void getViewDirection();
};

#endif /*CAMERA_H*/