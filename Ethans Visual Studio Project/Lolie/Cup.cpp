#include "Cup.h"
#include "CircleCollider.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#else
#include <GL/freeglut.h>
#include <SDL.h>
#endif

Cup::Cup(int id, Vector3f pos)
: pos(pos)
, tileID(id)
{
	color = { 0.0, 0.0, 0.0, 1.0 };
	dimensions.height = .05;
	dimensions.slices = 7;
	dimensions.radius = .06; 
	dimensions.stacks = 3;

	setCollider(CircleCollider(pos, dimensions.radius));
}

void Cup::update(float dt)
{
	// Update children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->update(dt);
	}
}

void Cup::draw()
{
	glPushMatrix();

	// create the quadratic
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	// Move the cylinder
	glTranslatef(pos.x, pos.y + .05, pos.z);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	// Set the color
	glColor4f(color.x, color.y, color.z, color.w);

	// Draw the cylinder
	gluCylinder(quadratic, dimensions.radius, dimensions.radius, dimensions.height, dimensions.slices, dimensions.stacks);

	glPopMatrix();

	// Draw children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->draw();
	}
}