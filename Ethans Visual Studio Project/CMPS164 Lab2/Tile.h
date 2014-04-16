#ifndef TILE_H
#define TILE_H

#include "utility.h"
#include <vector>

class Tile
{
public:
	Tile(int tileID, int numSides, std::vector<Vector3f> verts, std::vector<int> neigh)
		: tileID(tileID)
		, numSides(numSides)
		, vertList(verts)
		, neighbors(neigh) {}
private:
	std::vector<Vector3f> vertList;
	std::vector<int> neighbors;
	int tileID;
	int numSides;
};

#endif /* TILE_H */