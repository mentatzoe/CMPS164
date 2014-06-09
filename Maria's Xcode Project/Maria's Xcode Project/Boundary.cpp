#include "Boundary.h"
#include "LineCollider.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#else
#include <GL/freeglut.h>
#include <SDL.h>
#endif
#include <algorithm>

Boundary::Boundary(Vector3f vert1, Vector3f vert2, float height, bool physical)
: physical(physical)
{
	setType(Boundary_t);
	color.x = 1.0;
	color.y = 0.65;
	color.z = 0.0;
	color.w = 1.0;

	setCollider(new LineCollider(vert1, vert2));

	// Create the "upper" verticies
	Vector3f vert11(vert1.x, vert1.y + height, vert1.z);
	Vector3f vert22(vert2.x, vert2.y + height, vert2.z);

	// Push all them in to the vert list
	vertList.push_back(vert1);
	vertList.push_back(vert11);
	vertList.push_back(vert22);
	vertList.push_back(vert2);

	// Calc and set normal
	Vector3f normal = calcSurfaceNormal(vertList);
	normals.push_back(normal);

	// Reverse direction
	std::reverse(vertList.begin(), vertList.end());

	// ... So we can calc the other side's normal and push 
	normal = calcSurfaceNormal(vertList);
	normals.push_back(normal);

	// Then reverse again
	std::reverse(vertList.begin(), vertList.end());
}

void Boundary::update(float dt)
{
	// Update children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->update(dt);
	}
}

void Boundary::draw()
{
	// If regional boundary, do not draw
	if (!physical) return;
	
	// Else draw both polygons
	glColor4f(color.x, color.y, color.z, color.w);

	std::vector<Vector3f> verts = vertList;

	glBegin(GL_POLYGON);
	glNormal3f(normals[0].x, normals[0].y, normals[0].z);
	for (int i = 0; i < vertList.size(); i++) {
		glVertex3f(verts[i].x, verts[i].y, verts[i].z);
	}
	glEnd();

	std::reverse(verts.begin(), verts.end());

	glBegin(GL_POLYGON);
	glNormal3f(normals[1].x, normals[1].y, normals[1].z);
	for (int i = 0; i < vertList.size(); i++) {
		glVertex3f(verts[i].x, verts[i].y, verts[i].z);
	}
	glEnd();

	std::reverse(verts.begin(), verts.end());

	// Draw Children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->draw();
	}
}