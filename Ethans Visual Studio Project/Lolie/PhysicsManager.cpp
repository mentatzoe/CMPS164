#include "PhysicsManager.h"

void PhysicsManager::update(float dt, SceneNode& node)
{
	// Check collisions with sibling scenenodes
	SceneNode* parent = node.getParent();
	std::vector<SceneNode*> siblings = parent->getChildren();

	for (int i = 0; i < siblings.size(); i++) {
		Vector3f colPos;
		if (checkCollision(node, (*siblings[i]), colPos)){
			// There was a collision at point colPos

			// Do stuff
		}
	}
}

bool PhysicsManager::checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result)
{
	return node1.getCollider().getCollision(node2.getCollider(), result);
}