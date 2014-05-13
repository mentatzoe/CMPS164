#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "SceneNode.h"
#include "Ball.h"

class PhysicsManager 
{
public:
	static void update(float dt, Ball& b);
    static void giveImpulse(Vector3f f, float dt, Ball& b);
    static Vector3f getNextPosition(Vector3f p, Vector3f v, float dt);
private:
	static bool checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result);
};

#endif /* PHYSICSMANAGER_H */