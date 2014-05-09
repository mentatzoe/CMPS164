#ifndef BALL_H
#define BALL_H

#include "utility.h"
#include "SceneNode.h"

class Ball : public SceneNode {
public:
	Ball(int id, Vector3f pos);
	~Ball() {
    }

	void draw();
	void update(float dt);
    Vector3f getPosition(){return pos;};
    void setPosition(Vector3f p){pos = p;};
    float getMass(){return m;};
    Vector3f getV(){return v;};
    void setV(Vector3f vel){ v = vel;};
    
private:
	Vector3f pos;
    Vector3f v;
	int tileID;
    float m;

	Sphere dimensions;
	Vector4f color;
};

#endif /* BALL_H */