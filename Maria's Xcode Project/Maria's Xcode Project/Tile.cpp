#include "Tile.h"
#include "Boundary.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#else
#include <GL/freeglut.h>
#include <SDL.h>
#endif
#include <iostream>
#include <algorithm>


Tile::Tile(int tileID, int numSides, std::vector<Vector3f> verts, std::vector<int> neigh)
: tileID(tileID)
, numSides(numSides)
, vertList(verts)
, neighbors(neigh)
{
	setType(Tile_t);
	// Set color to GREEN
	color = { 0.0, 1.0, 0.0, 1.0 };

	Vector3f normal;
	std::vector<Vector3f> upper(verts.begin(), verts.end() - numSides);
	std::vector<Vector3f> lower(verts.begin() + numSides, verts.end());
	
	// Push the top surface normal on first
	normal = calcSurfaceNormal(upper);
	normals.push_back(normal);

	// Then push the bottom surface normal
	std::reverse(lower.begin(), lower.end());
	normal = calcSurfaceNormal(lower);
	std::reverse(lower.begin(), lower.end());
	normals.push_back(normal);

	// Then push the normals of the sides in
	for (int i = 0; i < numSides; i++) {
		std::vector<Vector3f> side;

		Vector3f vec = upper[i];
		side.push_back(vec);

		vec = lower[i];
		side.push_back(vec);

		vec = lower[(i + 1) % lower.size()];
		side.push_back(vec);

		vec = upper[(i + 1) % upper.size()];
		side.push_back(vec);

		normal = calcSurfaceNormal(side);
		normals.push_back(normal);
	}

	for (int i = 0; i < neigh.size(); i++){
		//Boundary bound(verts[i], verts[(i + 1) % verts.size()], .2, neigh[i] != 0);
		addChild(new Boundary(upper[i], upper[(i + 1) % upper.size()], 0.2f, neigh[i] == 0));
	}
}

void Tile::update(float dt)
{
	// Update children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->update(dt);
	}
}

void Tile::draw()
{
	std::vector<Vector3f> verts(vertList.begin(), vertList.end() - numSides);
	std::vector<Vector3f> lower(vertList.begin() + numSides, vertList.end());
	std::reverse(lower.begin(), lower.end());

	int normalIndex = 0;
	glColor4f(0.0, 1.0, 0.0, 1.0);

	// Draw Face 1
	glBegin(GL_POLYGON);
	glNormal3f(normals[normalIndex].x, normals[normalIndex].y, normals[normalIndex].z);
	for (int i = 0; i < numSides; i++) {
		glVertex3f(verts[i].x, verts[i].y, verts[i].z);
	}
	glEnd();
	normalIndex++;

	// Draw Face 2
	glBegin(GL_POLYGON);
	glNormal3f(normals[normalIndex].x, normals[normalIndex].y, normals[normalIndex].z);
	for (int i = 0; i < numSides; i++) {
		glVertex3f(lower[i].x, lower[i].y, lower[i].z);
	}
	glEnd();
	normalIndex++;

	std::reverse(lower.begin(), lower.end());

	// Draw Faces 3 to N
	for (int i = 0; i < numSides; i++) {
		glBegin(GL_POLYGON);
		glNormal3f(normals[normalIndex].x, normals[normalIndex].y, normals[normalIndex].z);
		glVertex3f(verts[i].x, verts[i].y, verts[i].z);
		glVertex3f(lower[i].x, lower[i].y, lower[i].z);
		glVertex3f(lower[(i + 1) % lower.size()].x, lower[(i + 1) % lower.size()].y, lower[(i + 1) % lower.size()].z);
		glVertex3f(verts[(i + 1) % verts.size()].x, verts[(i + 1) % verts.size()].y, verts[(i + 1) % verts.size()].z);
		glEnd();
		normalIndex++;
	}

	// Draw children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->draw();
	}
}