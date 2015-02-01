#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Cup.h"
#include "Tee.h"
#include "Ball.h"

class Level : public SceneNode
{
public:
	// Constructor
	Level();
	~Level() {}


	// Tick
	void update(float dt);
	void draw();
	
	// Getters / Setters
	Ball* getBall(){return b;};
    void setBall(Ball* ba){b = ba;};

	// Member Variables
    std::string levelName;
    int par;
private:
    Ball* b;
};

#endif /* LEVEL_H */