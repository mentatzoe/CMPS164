#ifndef TILE_H
#define TILE_H

#include "utility.h"

class Tile
{
public:
	Tile(int tileID, int numSides, std::vector<Vector3f> verts, std::vector<int> neigh);
	std::vector<Vector3f> getVerts() { return vertList; }
	std::vector<int> getNeighbors() { return neighbors; }
	int getTileID() { return tileID; }
	int getNumSides() { return numSides; }
	std::vector<Vector3f> getNormals() { return normals; }
private:
	std::vector<Vector3f> vertList;
	std::vector<int> neighbors;
	std::vector<Vector3f> normals;
	int tileID;
	int numSides;
};

#endif /* TILE_H */