#include "Level.h"
#include <vector>
#include "PhysicsManager.h"

Level::Level() 
{
	setType(SceneNode::Root_t);
}

void Level::update(float dt)
{
	// Run ball physics update
	PhysicsManager::update(dt, *b);

	// Update children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->update(dt);
	}
}

void Level::draw()
{
	// Draw children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->draw();
	}
}