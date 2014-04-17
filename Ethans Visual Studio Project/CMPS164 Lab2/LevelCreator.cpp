#include "LevelCreator.h"
#include <iostream>

Level LevelCreator::createLevel(TokenList tokenList)
{
	auto curToken = tokenList.begin();
	int tileID = 0;
	int numSides = 0;
	std::vector<Tile> tileList;
	Vector4f teeVect;
	Vector4f cupVect;
	std::vector<Vector3f> vertList;
	std::vector<int> neighbors;

	while (curToken != tokenList.end()) {
		//std::cout << "Examining curToken: " << (*curToken).data << "\n";
		if (curToken->data.compare("tile") == 0) {
			//std::cout << "     curToken is 'tile'\n";
			tileID = std::stoi((*std::next(curToken, 1)).data);
			numSides = std::stoi((*std::next(curToken, 2)).data);
			curToken += 3;

			//std::cout << "     (After tileID/numSides) curToken is now " << (*curToken).data << "\n";

			for (int i = 0; i < 3 * numSides; i += 3) {
				//std::cout << "curToken as a float is currently " << std::stof((std::next(curToken, i))->data) << "\n";
				Vector3f vert(std::stof((std::next(curToken, i))->data), std::stof((std::next(curToken, i + 1))->data), std::stof((std::next(curToken, i + 2))->data));
				vertList.push_back(vert);
			}
			curToken += 3 * numSides;

			//std::cout << "     (After verts) curToken is now " << (*curToken).data << "\n";

			for (int i = 0; i < numSides; i++) {
				neighbors.push_back(std::stof((std::next(curToken, i))->data));
			}
			curToken += numSides;

			//std::cout << "     (After neighbors) curToken is now " << (*curToken).data << "\n";

			Tile tile(tileID, numSides, vertList, neighbors);
			tileList.push_back(tile);
		}
		else if (curToken->data.compare("tee") == 0) {
			//std::cout << "     curToken is 'tee'\n";
			teeVect.x = std::stof((*std::next(curToken, 2)).data);
			teeVect.y = std::stof((*std::next(curToken, 3)).data);
			teeVect.z = std::stof((*std::next(curToken, 4)).data);
			teeVect.w = std::stof((*std::next(curToken, 1)).data);			// TileID
			curToken += 5;
		}
		else if (curToken->data.compare("cup") == 0) {
			//std::cout << "     curToken is 'cup'\n";
			cupVect.x = std::stof((*std::next(curToken, 2)).data);
			cupVect.y = std::stof((*std::next(curToken, 3)).data);
			cupVect.z = std::stof((*std::next(curToken, 4)).data);
			cupVect.w = std::stof((*std::next(curToken, 1)).data);			// TileID
			curToken += 5;
		}
		else {
			// Something wrong happened somewhere
			curToken++;
		}
	}

	Level level(tileList, teeVect, cupVect);
	return level;
}