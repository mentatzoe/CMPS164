#include "Level.h"
#include <vector>

Level::Level() {}

void Level::update(float dt)
{
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