#ifndef BALL_H
#define BALL_H

#include "utility.h"
#include "SceneNode.h"

class Ball : public SceneNode {
public:
	// Constructor
	Ball(int id, Vector3f pos);
	~Ball() {}

	// Tick
	void draw();
	void update(float dt);

	// Getters / Setters
    Vector3f getPosition(){return pos;};
    void setPosition(Vector3f p){pos = p;};
    Vector3f getV(){return v;};
    void setV(Vector3f vel){ v = vel;};
	float getMass(){ return m; };

	// Debug/Print
	void printPhysics();
private:
	// Member variables
	Vector3f pos, v;
	int tileID;
    float m;
	Sphere dimensions;
	Vector4f color;
};

#endif /* BALL_H */