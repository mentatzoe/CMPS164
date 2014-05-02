#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "SceneNode.h"
#include "utility.h"

class Boundary : public SceneNode
{
public:
	Boundary(Vector3f vert1, Vector3f vert2, float height);

	std::vector<Vector3f> getVerts() { return vertList; }
	std::vector<Vector3f> getNormals() { return normals; }
private:
	std::vector<Vector3f> vertList;
	std::vector<Vector3f> normals;

	Vector4f color;
};

#endif BOUNDARY_H