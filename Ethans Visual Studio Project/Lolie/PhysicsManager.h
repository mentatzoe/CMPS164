#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "SceneNode.h"

class PhysicsManager 
{
public:
	static void update(float dt, SceneNode& node);
private:
	static bool checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result);
};

#endif /* PHYSICSMANAGER_H */