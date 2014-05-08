#include "Cup.h"
#include <gl/freeglut.h>

Cup::Cup(int id, Vector3f pos)
: pos(pos)
, tileID(id)
{
	color = { 0.0, 0.0, 0.0, 1.0 };
	dimensions.height = .05;
	dimensions.slices = 7;
	dimensions.radius = .06; 
	dimensions.stacks = 3;
}

void Cup::update(float dt)
{
	for (auto itr = getChildren().begin(); itr != getChildren().end(); itr++) {
		(*itr)->update(dt);
	}
}

void Cup::draw()
{
	glPushMatrix();

	// create the quadratic
	GLUquadricObj *quadratic2;
	quadratic2 = gluNewQuadric();

	// Move the cylinder
	glTranslatef(pos.x, pos.y + .05, pos.z);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	// Set the color
	glColor4f(color.x, color.y, color.z, color.w);

	// Draw the cylinder
	gluCylinder(quadratic2, dimensions.radius, dimensions.radius, dimensions.height, dimensions.slices, dimensions.stacks);

	glPopMatrix();


	for (auto itr = getChildren().begin(); itr != getChildren().end(); itr++) {
		(*itr)->draw();
	}
}