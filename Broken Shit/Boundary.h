#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "SceneNode.h"
#include "utility.h"

class Boundary : public SceneNode
{
public:
	Boundary(Vector3f vert1, Vector3f vert2, float height, bool physics);

	void update(float dt);
	void draw();

	std::vector<Vector3f> getVerts() { return vertList; }
	std::vector<Vector3f> getNormals() { return normals; }

    bool isPhysical(){return physical;};
private:
	std::vector<Vector3f> vertList;
	std::vector<Vector3f> normals;

	bool physical;

	Vector4f color;
};

#endif BOUNDARY_H