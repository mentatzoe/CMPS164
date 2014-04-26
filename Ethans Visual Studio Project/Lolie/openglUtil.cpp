#include <gl/freeglut.h>
#include "openglUtil.h"

void drawCube()
{
	//Multi-colored side - FRONT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);     glVertex3f(0.5, -0.5, -0.5);      // P1 is red
	glColor3f(0.0, 1.0, 0.0);     glVertex3f(0.5, 0.5, -0.5);      // P2 is green
	glColor3f(0.0, 0.0, 1.0);     glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
	glColor3f(1.0, 0.0, 1.0);     glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple
	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
}

void drawTile(Tile tile, float thickness)
{
	std::vector<Vector3f> verts = tile.getVerts();
	std::vector<Vector3f> lowerVerts(verts.size());
	std::vector<int> neighs = tile.getNeighbors();
	Vector3f vec;
	std::vector<Vector3f> temp(4, vec);

	for (int i = 0; i < verts.size(); i++) {
		lowerVerts[i].x = verts[i].x;
		lowerVerts[i].y = verts[i].y - thickness;
		lowerVerts[i].z = verts[i].z;
	}

	Vector3f normal;
	glColor4f(0.0, 1.0, 0.0, 1.0);

	// Draw 6 tile faces

	// Face 1: A B C D (top)
	normal = calcSurfaceNormal(verts);
	glBegin(GL_POLYGON);
	glNormal3f(normal.x, normal.y, normal.z);
	for (Vector3f &v : verts){
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();

	// Face 2: A2 B2 C2 D2 (bottom)
	normal = calcSurfaceNormal(lowerVerts);
	glBegin(GL_POLYGON);
	glNormal3f(normal.x, normal.y, normal.z);
	for (auto v = lowerVerts.rbegin(); v != lowerVerts.rend(); v++){
		glVertex3f((*v).x, (*v).y, (*v).z);
	}
	glEnd();

	// Faces 3-n
	for (int i = 0; i < tile.getNumSides(); i++){
		temp[0] = verts[i];
		temp[1] = verts[(i + 1) % verts.size()];
		temp[2] = lowerVerts[(i + 1) % verts.size()];
		temp[3] = lowerVerts[i];
		normal = calcSurfaceNormal(temp);
		glBegin(GL_POLYGON);
		glNormal3f(normal.x, normal.y, normal.z);
		for (auto v = temp.rbegin(); v != temp.rend(); v++){
			glVertex3f((*v).x, (*v).y, (*v).z);
		}
		glEnd();
	}

	/*
	// Face 4: C D D2 C2
	temp[0] = verts[2];
	temp[1] = verts[3];
	temp[2] = lowerVerts[3];
	temp[3] = lowerVerts[2];
	normal = calcSurfaceNormal(temp);
	glBegin(GL_POLYGON);
	glNormal3f(normal.x, normal.y, normal.z);
	for (Vector3f &v : temp){
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();

	// Face 5: B C C2 B2
	temp[0] = verts[1];
	temp[1] = verts[2];
	temp[2] = lowerVerts[2];
	temp[3] = lowerVerts[1];
	normal = calcSurfaceNormal(temp);
	glBegin(GL_POLYGON);
	glNormal3f(normal.x, normal.y, normal.z);
	for (Vector3f &v : temp){
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();

	// Face 6: A B B2 A2
	temp[0] = verts[0];
	temp[1] = verts[1];
	temp[2] = lowerVerts[1];
	temp[3] = lowerVerts[0];
	normal = calcSurfaceNormal(temp);
	glBegin(GL_POLYGON);
	glNormal3f(normal.x, normal.y, normal.z);
	for (Vector3f &v : temp){
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	*/

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
	//Vector3f B(v1.x, v1.y - H, v1.z);
	//Vector3f C(v1.x, v1.y, v1.z);
	Vector3f D(v2.x, v2.y + H, v2.z);
	//Vector3f E(v2.x, v2.y - H, v2.z);
	//Vector3f F(v2.x, v2.y, v2.z);

	glColor4f(1, 0.65, 0.0, 1.0); // ORANGE

	/*
	// Face A B C V1
	glBegin(GL_POLYGON);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(C.x, C.y, C.z);
	glVertex3f(v1.x, v1.y, v1.z);
	glEnd();
	*/

	// Face D A v1 v2
	glBegin(GL_POLYGON);
	glVertex3f(D.x, D.y, D.z );
	glVertex3f(A.x , A.y, A.z );
	glVertex3f(v1.x , v1.y, v1.z );
	glVertex3f(v2.x , v2.y, v2.z );
	glEnd();

	/*
	// Face E D v2 F
	glBegin(GL_POLYGON);
	glVertex3f(E.x, E.y, E.z);
	glVertex3f(D.x, D.y, D.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(F.x, F.y, F.z);
	glEnd();

	// Face B E F C
	glBegin(GL_POLYGON);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(E.x, E.y, E.z);
	glVertex3f(F.x, F.y, F.z);
	glVertex3f(C.x, C.y, C.z);
	glEnd();

	// Face F v2 v1 C
	glBegin(GL_POLYGON);
	glVertex3f(F.x, F.y, F.z);
	glVertex3f(v2.x, v2.y, v2.z );
	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(C.x, C.y, C.z);
	glEnd();

	// Face B A D C
	glBegin(GL_POLYGON);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(D.x, D.y, D.z);
	glVertex3f(C.x, C.y, C.z);
	glEnd();
	*/
}