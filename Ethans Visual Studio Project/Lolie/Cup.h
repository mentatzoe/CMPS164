#ifndef CUP_H
#define CUP_H

#include "SceneNode.h"

class Cup : public SceneNode
{
public:
	Cup(int id, Vector3f pos);
	~Cup() {}

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

#endif /* CUP_H */