#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#else
#include <GL/freeglut.h>
#include <SDL.h>
#endif

#include "Ball.h"
#include "Tile.h"
#include "LineCollider.h"
#include "PhysicsManager.h"

Ball::Ball(int id, Vector3f pos)
: pos(pos)
, tileID(id)
{
	setType(Ball_t);
	color = { 1.0, 1.0, 1.0, 1.0 };
	dimensions.slices = 11;
	dimensions.radius = .055;
	dimensions.stacks = 5;
    m = 9000;
    v = Vector3f(0, 0, 0);

	setCollider(new LineCollider(pos, pos));
}

void Ball::update(float dt)
{
	/// Update Y position ///
	SceneNode* node = getParent();
	Vector3f up(0, 1, 0);

	// Asserting that Ball's parent is a tile
	Tile* parent = static_cast<Tile*>(node);
	Vector3f tileNormal = parent->getNormals()[0]; // First normal is the normal of the top surface

	// Line is p = d(l) + l0 where l0 is a point on the line (Ball's pos) and l is a vector in the direction of line (tile normal)

	// Calculate scalar of the point of collision
	float d = dot((parent->getVerts()[0] - pos), tileNormal) / dot(up, tileNormal);
	
	// Turn scalar and line equation into point
	Vector3f colPoint = (up * d) + pos;

	// Set the position of ball to the position of the collision + the radius in the direction of the normal.
	pos.y = colPoint.y + dimensions.radius;
    getCollider()->setA(pos);

	//std::cout << "Set Ball Y to " << pos.y << "\n";

	// Update children
 	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->update(dt);
	}
}

void Ball::draw()
{
	glPushMatrix();

	// create the quadratic
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	// Move the Sphere
	glTranslatef(pos.x, pos.y, pos.z);

	// Set Color
	glColor4f(color.x, color.y, color.z, color.w);

	// Draw Sphere
	gluSphere(quadratic, dimensions.radius, dimensions.slices, dimensions.stacks);

	glPopMatrix();

	// Draw children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->draw();
	}
}

void Ball::printPhysics()
{
	std::cout << "     A - Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
	std::cout << "     B - Position: (" << getCollider()->getB().x << ", " << getCollider()->getB().y << ", " << getCollider()->getB().z << ")\n";
	std::cout << "     Velocity: (" << v.x << ", " << v.y << ", " << v.z << ")\n";
	std::cout << "     Parent Tile: " << static_cast<Tile*>(getParent())->getTileID() << "\n";
}