#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "SceneNode.h"
#include "Ball.h"
#include "Tile.h"
#include "Boundary.h"

class PhysicsManager 
{
public:
	static void update(float dt, Ball& b);
    static void giveImpulse(Vector3f f, float dt, Ball& b);
    static Vector3f getNextPosition(Vector3f p, Vector3f v, float dt, Vector3f a);
private:
	static bool checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result);
	static float calcIncline(Vector3f normal);
	static float calcTilt(Vector3f normal);
	static Vector3f calcAcceleration(Vector3f tileNormal);
	static Vector3f calcReflectVelo(Vector3f boundNormal, Vector3f ballVelo);
	static float calcRemainingTime(Vector3f p1, Vector3f p2, Vector3f colPos, float dt);
	static void setNewParent(Tile* parentTile, Boundary* bound, Ball& b);
	static Vector3f updateV(Vector3f v, Vector3f a, float dt);
	static Vector3f dampenVelo(Vector3f v);
};

#endif /* PHYSICSMANAGER_H */