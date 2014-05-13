#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Cup.h"
#include "Tee.h"

class Level : public SceneNode
{
public:
	Level();
	~Level() {}

	void update(float dt);
	void draw();
};

#endif /* LEVEL_H */