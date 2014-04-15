#include "utility.h"
#include <vector>

class Tile
{
public:
	Tile(std::vector<Vector3f> verts, std::vector<int> neigh, int tileID, int numSides)
		: vertList(verts)
		, neighbors(neigh)
		, tileID(tileID)
		, numSides(numSides) {}
private:
	std::vector<Vector3f> vertList;
	std::vector<int> neighbors;
	int tileID;
	int numSides;
}