#ifndef SCENENODE_H
#define SCENENODE_H

#include "utility.h"
#include "Collider2D.h"

class SceneNode
{
public:
	enum Type {
		Tile_t,
		Tee_t,
		Cup_t,
		Ball_t,
		Boundary_t,
	};

	void setParent(SceneNode* node) { parent = node; }
	SceneNode* getParent() { return parent; }

	void addChild(SceneNode* node);
	std::vector<SceneNode*> getChildren() { return children; }

	void setType(Type type) { myType = type; }
	Type getType() { return myType; }

	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	void setCollider(Collider2D* col) { collider = col; }
	Collider2D* getCollider() { return collider; }
protected:
	SceneNode();
private:
	Type myType;
	SceneNode* parent;
	std::vector<SceneNode*> children;

	Collider2D* collider;
};

#endif /* SCENENODE_H */
