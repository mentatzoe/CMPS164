#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "SceneNode.h"
#include "Ball.h"

class PhysicsManager 
{
public:
	static void update(float dt, Ball& b);
private:
	static bool checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result);
    static void giveImpulse(Vector3f f, float dt, Ball& b);
};

#endif /* PHYSICSMANAGER_H */