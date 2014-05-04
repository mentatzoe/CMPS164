#include "SceneNode.h"

SceneNode::SceneNode()
{
	parent = nullptr;
}

SceneNode::~SceneNode()
{
	for (int i = 0; i < children.size(); i++){
		delete children[i];
	}
}

void SceneNode::update(float dt)
{
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->update(dt);
	}
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