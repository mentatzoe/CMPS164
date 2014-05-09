#include "SceneNode.h"

SceneNode::SceneNode()
{
	parent = nullptr;
}

void SceneNode::addChild(SceneNode* node)
{
	children.push_back(node);
	node->parent = this;
}
