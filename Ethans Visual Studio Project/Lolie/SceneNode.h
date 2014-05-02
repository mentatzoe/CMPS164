#ifndef SCENENODE_H
#define SCENENODE_H

#include "utility.h"

class SceneNode
{
public:
	SceneNode();
	~SceneNode();

	void addChild(SceneNode* node);
	void update(float dt);

	virtual std::vector<Vector3f> getNormals() = 0;
private:
	SceneNode* parent;
	std::vector<SceneNode*> children;
};

#endif /* SCENENODE_H */
