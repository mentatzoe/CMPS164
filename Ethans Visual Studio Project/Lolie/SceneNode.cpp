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

std::vector<Vector3f> SceneNode::getNormals()
{
	std::vector<Vector3f> empty;
	return empty;
}