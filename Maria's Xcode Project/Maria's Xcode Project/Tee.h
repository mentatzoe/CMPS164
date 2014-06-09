#ifndef TEE_H
#define TEE_H

#include "SceneNode.h"

class Tee : public SceneNode
{
public:
	// Constructor
	Tee(int id, Vector3f pos);
	~Tee() {}

	// Getters / Setters
	Vector3f getPos() { return pos; }
	int getTileID() { return tileID; }
	Vector4f getColor() { return color; }
	Cylinder getDimensions() { return dimensions; }

	// Tick
	void update(float dt);
	void draw();
private:
	// Member Variables
	Vector3f pos;
	int tileID;
	Cylinder dimensions;
	Vector4f color;
};

#endif /* TEE_H */

