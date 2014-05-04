#ifndef TEE_H
#define TEE_H

#include "SceneNode.h"

class Tee : public SceneNode
{
public:
	Tee(int id, Vector3f pos);
	~Tee() {}

	Vector3f getPos() { return pos; }
	int getTileID() { return tileID; }
	Vector4f getColor() { return color; }
	Cylinder getDimensions() { return dimensions; }
private:
	Vector3f pos;
	int tileID;

	Cylinder dimensions;
	Vector4f color;
};

#endif /* TEE_H */

