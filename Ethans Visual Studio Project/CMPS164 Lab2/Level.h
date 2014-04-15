#include "utility.h"
#include <vector>
#include "Tile.h"

class Level
{
public:
	Level(std::vector<Tile> tileList, Vector4f teeVect, Vector4f cupVect)
		: tileList(tileList)
		, tee(teeVect)
		, cup(cupVect) {}
private:
	std::vector<Tile> tileList;
	Vector4f tee;
	Vector4f cup;
};