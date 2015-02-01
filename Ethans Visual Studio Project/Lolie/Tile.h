#ifndef TILE_H
#define TILE_H

#include "utility.h"
#include "SceneNode.h"

class Tile : public SceneNode
{
public:
	// Constructor
	Tile(int tileID, int numSides, std::vector<Vector3f> verts, std::vector<int> neigh);

	// Getters / Setters
	std::vector<Vector3f> getVerts() { return vertList; }
	std::vector<int> getNeighbors() { return neighbors; }
	int getTileID() { return tileID; }
	int getNumSides() { return numSides; }
	std::vector<Vector3f> getNormals() { return normals; }

	// Tick
	void update(float dt);
	void draw();
private:
	// Member Variables
	std::vector<Vector3f> vertList, normals;
	std::vector<int> neighbors;
	int tileID, numSides;
	Vector4f color;
};

#endif /* TILE_H */