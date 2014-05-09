#ifndef BALL_H
#define BALL_H

#include "utility.h"
#include "SceneNode.h"

class Ball : public SceneNode {
public:
	Ball(int id, Vector3f pos);
	~Ball();

	void draw();
	void update(float dt);
private:
	Vector3f pos;
	int tileID;

	Sphere dimensions;
	Vector4f color;
};

#endif /* BALL_H */