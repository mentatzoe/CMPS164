#ifndef CUP_H
#define CUP_H

#include "SceneNode.h"

class Cup : public SceneNode
{
public:
	// Constructor
	Cup(int id, Vector3f pos);
	~Cup() {}

	// Getters / Setters
	Vector3f getPos() { return pos; }
	int getTileID() { return tileID; }
	Vector4f getColor() { return color; }
	Cylinder getDimensions() { return dimensions; }

	// Tick
	void update(float dt);
	void draw();
private:
	// Member variables
	Vector3f pos;
	int tileID;
	Cylinder dimensions;
	Vector4f color;
};

#endif /* CUP_H */