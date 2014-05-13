#include "Camera.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#else
#include <GL/freeglut.h>
#include <SDL.h>
#endif

const float PIdiv180 (3.1415265359 / 180.0);

Camera::Camera()
{
	position = Vector3f(0, 3, 3);
	viewDir = Vector3f(0, 0, -1);

	rotatedX = rotatedY = rotatedZ = 0.0;
	viewDirChanged = false;
}

void Camera::setPosition(Vector3f pos)
{
	position = pos;
}

void Camera::update()
{
	getViewDirection();
}

void Camera::setFreeLook()
{
	position = Vector3f(0, 3, 3);
	viewDir = Vector3f(0, 0, -1);

	rotatedX = rotatedY = rotatedZ = 0.0;
	rotateX(-50);
}

void Camera::setTopDown()
{
	position = Vector3f(0, 4, 0);
	viewDir = Vector3f(0, 0, -1);

	rotatedX = rotatedY = rotatedZ = 0.0;
	rotateX(-90);
}

void Camera::setballCamera(Ball* ball)
{
	Vector3f ballPos = ball->getPosition();
	position = Vector3f(ballPos.x -.1f, ballPos.y+.195f, ballPos.z+.12f);
	rotatedX = rotatedY = rotatedZ = 0.0;
	rotateX(-30);
	rotateY(-30);
}

void Camera::getViewDirection()
{
	Vector3f Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos((rotatedY + 90.0f) * PIdiv180);
	Step1.z = -sin((rotatedY + 90.0f) * PIdiv180);
	//Rotate around X-axis:
	float cosX = cos(rotatedX * PIdiv180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(rotatedX * PIdiv180);
	//Rotation around Z-axis not yet implemented, so:
	viewDir = Step2;
}

void Camera::render()
{
	glRotatef(-rotatedX, 1.0, 0.0, 0.0);
	glRotatef(-rotatedY, 0.0, 1.0, 0.0);
	glRotatef(-rotatedZ, 0.0, 0.0, 1.0);
	glTranslatef(-position.x, -position.y, -position.z);
}

void Camera::move(Vector3f direction)
{
	position = position + direction;
}

void Camera::moveForwards(float distance)
{
	if (viewDirChanged) getViewDirection();
	Vector3f moveVect;
	moveVect.x = viewDir.x * -distance;
	moveVect.y = viewDir.y * -distance;
	moveVect.z = viewDir.z * -distance;
	position = position + moveVect;
}

void Camera::moveUp(float distance)
{
	if (viewDirChanged) getViewDirection();
	Vector3f moveVect;
	moveVect.x = viewDir.x * -distance;
	moveVect.y = viewDir.y * -distance;
	moveVect.z = viewDir.z * -distance;
	position = position + moveVect;
}

void Camera::strafeRight(float distance)
{
	if (viewDirChanged) getViewDirection();
	Vector3f moveVect;
	moveVect.x = viewDir.z * -distance;
	moveVect.y = 0;
	moveVect.z = -viewDir.x * -distance;
	position = position + moveVect;
}

void Camera::rotateX(float angle)
{
	rotatedX += angle;
	viewDirChanged = true;
}

void Camera::rotateY(float angle)
{
	rotatedY += angle;
	viewDirChanged = true;
}

void Camera::rotateZ(float angle)
{
	rotatedZ += angle;
	viewDirChanged = true;
}

Vector3f Camera::getRotates(){
	return Vector3f(rotatedX, rotatedY, rotatedZ);
}