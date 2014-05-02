#include <gl/freeglut.h>
#include "openglUtil.h"

void drawTile(Tile tile) {
	int numSides = tile.getNumSides();
	std::vector<Vector3f> vertList(tile.getVerts());
	std::vector<Vector3f> verts(vertList.begin(), vertList.end() - numSides);
	std::vector<Vector3f> lower(vertList.begin() + numSides, vertList.end());
	std::vector<int> neighs = tile.getNeighbors();
	std::vector<Vector3f> normals = tile.getNormals();

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

	// Draw Faces 3 to N
	for (int i = 0; i < numSides; i++) {
		glBegin(GL_POLYGON);
		glNormal3f(normals[normalIndex].x, normals[normalIndex].y, normals[normalIndex].z);
		glVertex3f(verts[i].x, verts[i].y, verts[i].z);
		glVertex3f(verts[(i + 1) % verts.size()].x, verts[(i + 1) % verts.size()].y, verts[(i + 1) % verts.size()].z);
		glVertex3f(lower[(i + 1) % lower.size()].x, lower[(i + 1) % lower.size()].y, lower[(i + 1) % lower.size()].z);
		glVertex3f(lower[i].x, lower[i].y, lower[i].z);
		glEnd();
		normalIndex++;
	}

	// Draw Boundaries
	for (int i = 0; i < neighs.size(); i++){
		if (neighs[i] == 0) {
			// No neighbor, draw boundary between verts i and i+1
			drawBoundary(verts[i], verts[(i + 1) % verts.size()], .2);
		}
	}
}

void drawBoundary(Vector3f v1, Vector3f v2, float H)
{
	Vector3f A(v1.x, v1.y + H, v1.z);
	Vector3f D(v2.x, v2.y + H, v2.z);

	glColor4f(1, 0.65, 0.0, 1.0); // ORANGE

	// Face D A v1 v2
	glBegin(GL_POLYGON);
	glVertex3f(D.x, D.y, D.z );
	glVertex3f(A.x , A.y, A.z );
	glVertex3f(v1.x , v1.y, v1.z );
	glVertex3f(v2.x , v2.y, v2.z );
	glEnd();
}