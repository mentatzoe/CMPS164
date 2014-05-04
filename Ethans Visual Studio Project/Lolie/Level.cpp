#include "Level.h"
#include <iostream>

void Level::print()
{
	std::cout << "Printing Level Status:\n";
	for (auto itr = tileList.begin(); itr != tileList.end(); itr++){
		std::cout << "     Tile with ID = " << (*itr).getTileID() << " and numSides = " << (*itr).getNumSides() << "\n";
		std::vector<Vector3f> verts = (*itr).getVerts();
		for (int i = 0; i < verts.size(); i++) {
			std::cout << "          Vertex " << i << ": [" << verts[i].x << ", " << verts[i].y << ", " << verts[i].z << "]\n";
		}
		std::vector<int> neighbors = (*itr).getNeighbors();
		std::cout << "          Neighbors list: ";
		for (int i = 0; i < neighbors.size(); i++){
			std::cout << neighbors[i] << ", ";
		}
		std::cout << "\n";
		std::vector<Vector3f> normals = (*itr).getNormals();

		for (int i = 0; i < normals.size(); i++) {
			std::cout << "          Normal " << i << ": [" << normals[i].x << ", " << normals[i].y << ", " << normals[i].z << "]\n";
		}
		std::cout << "\n";
	}
	Vector3f teePos = tee.getPos();
	Vector3f cupPos = cup.getPos();

	std::cout << "     Tee: [" << teePos.x << ", " << teePos.y << ", " << teePos.z << "] on tile " << tee.getTileID() << "\n";
	std::cout << "     Cup: [" << cupPos.x << ", " << cupPos.y << ", " << cupPos.z << "] on tile " << cup.getTileID() << "\n";
}