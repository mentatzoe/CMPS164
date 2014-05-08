#include "Boundary.h"
#include <gl/freeglut.h>
#include <algorithm>

Boundary::Boundary(Vector3f vert1, Vector3f vert2, float height, bool physical) 
{
	color.x = 1.0;
	color.y = 0.65;
	color.z = 0.0;
	color.w = 1.0;

	Vector3f vert11(vert1.x, vert1.y + height, vert1.z);
	Vector3f vert22(vert2.x, vert2.y + height, vert2.z);

	vertList.push_back(vert1);
	vertList.push_back(vert11);
	vertList.push_back(vert22);
	vertList.push_back(vert2);

	Vector3f normal = calcSurfaceNormal(vertList);
	normals.push_back(normal);

	std::reverse(vertList.begin(), vertList.end());

	normal = calcSurfaceNormal(vertList);
	normals.push_back(normal);

	std::reverse(vertList.begin(), vertList.end());
}

void Boundary::update(float dt)
{
	for (auto itr = getChildren().begin(); itr != getChildren().end(); itr++) {
		(*itr)->update(dt);
	}
}

void Boundary::draw()
{
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

	for (auto itr = getChildren().begin(); itr != getChildren().end(); itr++) {
		(*itr)->draw();
	}
}