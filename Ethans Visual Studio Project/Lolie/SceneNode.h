#ifndef SCENENODE_H
#define SCENENODE_H

#include "utility.h"

class SceneNode
{
public:
	void setParent(SceneNode* node) { parent = node; }
	SceneNode* getParent() { return parent; }

	void addChild(SceneNode* node);
	std::vector<SceneNode*> getChildren() { return children; }

	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual std::vector<Vector3f> getNormals();
protected:
	SceneNode();
private:
	SceneNode* parent;
	std::vector<SceneNode*> children;
};

#endif /* SCENENODE_H */
