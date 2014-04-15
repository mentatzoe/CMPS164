#include "LevelCreator.h"

Level LevelCreator::createLevel(TokenList tokenList)
{
	auto curToken = tokenList.begin();
	int tileID = 0;
	int numSides = 0;
	std::vector<Tile> tileList;
	Vector3f teeVect;
	Vector3f cupVect;

	while (curToken != tokenList.end()) {
		switch ((curToken)->data) {
		case "tile":
			std::vector<Vector3f> vertList;
			std::vector<int> neighbors;

			tileID = *std::next(curToken, 1).data;
			numSides = *std::next(curToken, 2).data;
			curToken += 3;

			for (int = 0; i < 3 * numSides; i += 3) {
				Vector3f vert(*std::next(curToken, i).data, *std::next(curToken, i + 1).data, *std::next(curToken, i + 2).data);
				vertList.push_back(vert);
			}
			curToken += 3 * numSides;

			for (int i = 0; i < numSides; i++) {
				neighbors.push_back(*std::next(curToken, i).data);
			}
			curToken += numSides;

			Tile tile(tileID, numSides, vertList, neighbors);
			tileList.push_back(tile);
			break;

		case "tee":
			teeVect.x = *std::next(curToken, 2).data;
			teeVect.y = *std::next(curToken, 3).data;
			teeVect.z = *std::next(curToken, 4).data;
			teeVect.w = *std::next(curToken, 1).data;			// TileID
			break;

		case "cup":
			cupVect.x = *std::next(curToken, 2).data;
			cupVect.y = *std::next(curToken, 3).data;
			cupVect.z = *std::next(curToken, 4).data;
			cupVect.w = *std::next(curToken, 1).data;			// TileID
			break;

		case '\n':
			// Means that there is some extra white space somewhere
			curToken++;
			break;

		default:
			// Something wrong happened somewhere
			break;
		}
	}

	Level level(tileList teeVect, cupVect);
	return level;
}