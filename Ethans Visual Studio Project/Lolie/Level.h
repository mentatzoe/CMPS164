#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Cup.h"
#include "Tee.h"

class Level
{
public:
	Level(std::vector<Tile> tileList, Tee tee, Cup cup)
		: tileList(tileList)
		, tee(tee)
		, cup(cup) {}
	~Level() {}
	void print();
    std::vector<Tile> getTileList() {return tileList;};
    Tee getTee() {return tee;};
    Cup getCup() {return cup;};
private:
	std::vector<Tile> tileList;
	Tee tee;
	Cup cup;
};

#endif /* LEVEL_H */