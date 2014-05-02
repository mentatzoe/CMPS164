#include "Boundary.h"
#include <algorithm>

Boundary::Boundary(Vector3f vert1, Vector3f vert2, float height) 
{
	color.x = 1.0;
	color.y = 0.65;
	color.z = 0.0;
	color.w = 1.0;

	Vector3f vert11(vert1.x, vert1.y + height, vert1.z);
	Vector3f vert22(vert2.x, vert2.y + height, vert2.z);

	vertList.push_back(vert2);
	vertList.push_back(vert22);
	vertList.push_back(vert11);
	vertList.push_back(vert1);

	Vector3f normal = calcSurfaceNormal(vertList);
	normals.push_back(normal);

	std::reverse(vertList.begin(), vertList.end());

	normal = calcSurfaceNormal(vertList);
	normals.push_back(normal);
}