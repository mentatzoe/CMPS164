#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "utility.h"

class Level
{
public:
	Level(std::vector<Tile> tileList, Vector4f teeVect, Vector4f cupVect)
		: tileList(tileList)
		, tee(teeVect)
		, cup(cupVect) {}
	void print();
private:
	std::vector<Tile> tileList;
	Vector4f tee;
	Vector4f cup;
};

#endif /* LEVEL_H */