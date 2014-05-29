#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "SceneNode.h"
#include "Ball.h"

class PhysicsManager 
{
public:
	static void update(float dt, Ball& b);
    static void giveImpulse(Vector3f f, float dt, Ball& b);
    static Vector3f getNextPosition(Vector3f p, Vector3f v, float dt, Vector3f a);
private:
	static bool checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result);
	static float calcIncline(Vector3f normal);
	static float calcTilt(Vector3f normal);
	static Vector3f calcAcceleration(float theta, float phi);
	static Vector3f updateV(Vector3f v, Vector3f a, float dt);
};

#endif /* PHYSICSMANAGER_H */