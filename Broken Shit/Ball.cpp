#include "Ball.h"

void Ball::draw() 
{
	glPushMatrix();
	
	glTranslatef(location.x, location.y, location.z);
	sphere.draw();

	glPopMatrix();
}