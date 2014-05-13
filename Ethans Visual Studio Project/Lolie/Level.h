#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Cup.h"
#include "Tee.h"
#include "Ball.h"

class Level : public SceneNode
{
public:
	Level();
	~Level() {}

	void update(float dt);
	void draw();
    Ball* getBall(){return b;};
    void setBall(Ball* ba){b = ba;};
private:
    Ball* b;
};

#endif /* LEVEL_H */