#include "Tile.h"
#include <iostream>
Tile::Tile(int tileID, int numSides, std::vector<Vector3f> verts, std::vector<int> neigh)
: tileID(tileID)
, numSides(numSides)
, vertList(verts)
, neighbors(neigh)
{
	Vector3f normal;
	std::vector<Vector3f> upper(verts.begin(), verts.end() - numSides);
	std::vector<Vector3f> lower(verts.begin() + numSides, verts.end());
	
	// Push the top surface normal on first
	normal = calcSurfaceNormal(upper);
	normals.push_back(normal);

	// Then push the bottom surface normal
	normal = calcSurfaceNormal(lower);
	normals.push_back(normal);

	// Then push the normals of the sides in
	for (int i = 0; i < numSides; i++) {
		std::vector<Vector3f> side;

		Vector3f vec = upper[i];
		side.push_back(vec);

		vec = upper[(i + 1) % upper.size()];
		side.push_back(vec);

		vec = lower[(i + 1) % lower.size()];
		side.push_back(vec);

		vec = lower[i];
		side.push_back(vec);

		normal = calcSurfaceNormal(side);
		normals.push_back(normal);
	}
}