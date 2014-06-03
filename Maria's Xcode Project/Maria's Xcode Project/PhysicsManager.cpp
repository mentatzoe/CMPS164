#include "PhysicsManager.h"
#include "Boundary.h"
#include "Tile.h"
#include "Cup.h"
#include "Tee.h"
#include "LineCollider.h"
#include "GameInfo.h"

const float PI = 3.14159f;

Vector3f a(0, 0, 0);
Vector3f up(0, 1, 0);
Vector3f x(1, 0, 0);
Vector3f z(0, 0, 1);

void PhysicsManager::update(float dt, Ball& b)
{
	// Declarations
	float timeLeft;
	Vector3f v_init, p_init, p_new, p, v, colPos, tileNormal;
	SceneNode* parent = b.getParent();
	std::vector<SceneNode*> siblings = parent->getChildren();

	// Get initial position and velocity
	v_init = b.getV();
	p_init = b.getPosition();

	// Calculate Acceleration
	Tile* parentTile = static_cast<Tile*>(parent);
	tileNormal = parentTile->getNormals()[0];
	a = calcAcceleration(tileNormal);

	// Calculate new position
	p = getNextPosition(p_init, v_init, dt, a);

	// Set Line Collider
	b.getCollider()->setA(p_init);
	b.getCollider()->setB(p);

	timeLeft = dt;
	bool collisions = true;
	while (collisions){

		//Check collision with siblings
		for (int i = 0; i < siblings.size(); i++) {

			// When we find the ball in sibling list, skip it
			if ((*siblings[i]).getType() == SceneNode::Ball_t){
				i++;
				if (i == siblings.size()){
					continue;
				}
			}

			if (checkCollision(b, (*siblings[i]), colPos)){
				switch (siblings[i]->getType()){
				case SceneNode::Tile_t:
					//Tile* tile = static_cast<Tile*>(siblings[i]);
					break;
				case SceneNode::Tee_t:
					//Tee* tee = static_cast<Tee*>(siblings[i]);
				//	b.setV(Vector3f(0, 0, 0));
					break;
				case SceneNode::Cup_t:
					//Cup* cup = static_cast<Cup*>(siblings[i]);
					std::cout << "Hit the cup!\n";
					if (magnitude(b.getV()) < .0008 && magnitude(b.getV()) != 0){
						std::cout << "MADE IT IN!\n";
						GameInfo::nextLevel();
                        GameInfo::strokes = 0;
					}
					break;
				case SceneNode::Ball_t:
					break;
				case SceneNode::Boundary_t:
					Boundary* bound = static_cast<Boundary*>(siblings[i]);
					
					// If we collide with a physical boundary
					if (bound->isPhysical()){
						std::cout << "Collided with a physical boundary!\n";

						// Calculate reflected velocity
						Vector3f vReflected = calcReflectVelo(bound->getNormals()[1], b.getV());

						// Calculate time it takes to reach colPos
						timeLeft = calcRemainingTime(p_init, p, colPos, timeLeft);

						// Find new line given initial position is colPos and new velocity/pos and new time
						p_new = getNextPosition(colPos, vReflected, timeLeft, a);

						// Update the Ball
						b.setPosition(colPos);
						b.setV(vReflected);
						b.getCollider()->setA(colPos);
						b.getCollider()->setB(p_new);

						// Loop to see if anything has been collided with
						continue;

					// Else we collided with a region change boundary
					}
					else{

						std::cout << "Collided with a regional boundary!\n";

						std::cout << "Before calc: \n";
						b.printPhysics();
						
						// Calculate time it takes to reach colPos
						timeLeft = calcRemainingTime(p_init, p, colPos, timeLeft);

						// Update the Ball
						b.setPosition(colPos);
						b.getCollider()->setA(colPos);

						// Set new Parent
						setNewParent(parentTile, bound, b);

						// Recalculate A
						tileNormal = static_cast<Tile*>(b.getParent())->getNormals()[0];
						a = calcAcceleration(tileNormal);

						// Find new line given initial position is colPos and new time
						p_new = getNextPosition(colPos, b.getV(), timeLeft, a);

						// Update the new pos
						b.getCollider()->setB(p_new);

						std::cout << "After calc: \n";
						b.printPhysics();

						// Loop to see if anything has been collided with
						continue;
					}
					break;
				}
			}
		}
		// If we collide with nothing, turn exit loop
		collisions = false;
	}

	// We finished with no collisions, calculate final pos
	p_new = getNextPosition(b.getPosition(), b.getV(), timeLeft, a);

	b.setPosition(p_new);
	b.getCollider()->setA(p_new);

	// Update V given A
	b.setV(updateV(dampenVelo(b.getV()), a, timeLeft));

	// Debug lines
	std::cout << "     Velocity: (" << b.getV().x << ", " << b.getV().y << ", " << b.getV().z << ")\n";
	std::cout << "     Acceleration: (" << a.x << ", " << a.y << ", " << a.z << ")\n";
	std::cout << "=============================\n";
}

void PhysicsManager::setNewParent(Tile* parentTile, Boundary* bound, Ball& b)
{
	// Declarations
	std::vector<Vector3f> tileVerts = parentTile->getVerts();
	std::vector<Vector3f> upper(tileVerts.begin(), tileVerts.end() - parentTile->getNumSides());
	std::vector<Vector3f> boundVerts = bound->getVerts();
	std::vector<int> neighbors = parentTile->getNeighbors();

	// Iterate through list of tile's verts
	for (int i = 0; i < upper.size(); i++) {

		// Find the pair of verts that created the boundary
		if (boundVerts[0] == upper[i] && boundVerts[3] == upper[(i + 1) % upper.size()]) {

			// Now the correct tileID for ball is the neigh[i]
			//SceneNode* level = parent->getParent();
			std::vector<SceneNode*> tiles = parentTile->getParent()->getChildren();

			// Find the tile that has the matching tileID
			for (SceneNode* tile : tiles) {
				if (tile->getType() == SceneNode::Tile_t){
					Tile* curTile = static_cast<Tile*>(tile);

					// Set ball's new parent if we find the correct tile
					if (curTile->getTileID() == neighbors[i]){
						b.setParent(curTile);
					}
				}
			}
		}
	}
}

float PhysicsManager::calcRemainingTime(Vector3f p1, Vector3f p2, Vector3f colPos, float dt)
{
	float distA = distanceNoY(p1, p2);
	float distB = distanceNoY(p1, colPos);
	float timeToColPos = (distB * dt) / distA;

	return (dt - timeToColPos);
}

Vector3f PhysicsManager::calcReflectVelo(Vector3f boundNormal, Vector3f ballVelo)
{
	float dotProductIN = boundNormal.x * -ballVelo.x + boundNormal.z * -ballVelo.z;
	Vector3f temp = Vector3f(2 * dotProductIN * boundNormal.x, 2 * dotProductIN * boundNormal.y, 2 * dotProductIN * boundNormal.z);
	return Vector3f(temp.x + ballVelo.x, 0, temp.z + ballVelo.z);
}

float PhysicsManager::calcIncline(Vector3f normal)
{
	float theta = acos(dot(normal, up) / (magnitude(normal) * magnitude(up)));
	return theta;
}

float PhysicsManager::calcTilt(Vector3f normal)
{
	float phi;
	normal.y = 0;
	if (normal.x > 0){
		phi = acos(dot(normal, z) / (magnitude(normal) * magnitude(z)));
	}
	else{
		phi = -acos(dot(normal, z) / (magnitude(normal) * magnitude(z)));
	}

	if (phi == -PI) phi = 0;

	return phi;
}

Vector3f PhysicsManager::calcAcceleration(Vector3f tileNormal)
{


	float theta = calcIncline(tileNormal);
	float phi = calcTilt(tileNormal);

	Vector3f a;
	if (theta > 0){
		a = Vector3f(-1 * (-0.0000058 * sin(theta) * sin(phi)), 0, -1 * (-0.0000058 * sin(theta) * cos(phi)));
	}
	else{
		a = Vector3f(0, 0, 0);
	}
	return a;
}

Vector3f PhysicsManager::getNextPosition(Vector3f p, Vector3f v, float dt, Vector3f a){
    return Vector3f(p.x + v.x*dt + 0.5f*dt*dt*a.x,
                    p.y + v.y*dt + 0.5f*dt*dt*a.y,
                    p.z + v.z*dt + 0.5f*dt*dt*a.z);
}

Vector3f PhysicsManager::updateV(Vector3f v, Vector3f a, float dt)
{
	Vector3f v_new;
	v_new.x = v.x + (a.x * dt);
	v_new.y = v.y + (a.y * dt);
	v_new.z = v.z + (a.z * dt);
	return v_new;
}

Vector3f PhysicsManager::dampenVelo(Vector3f v)
{
	if (v.x != 0 || v.y != 0 || v.z != 0){
		float speed = magnitude(v);
		Vector3f direction = normalize(v);
		if (speed > 0) speed *= 0.9888f;
		else speed = 0;
		Vector3f velo = direction * speed;
		if (velo.x < .00004 && velo.x > -.00004){
			velo.x = 0;
		}
		if (velo.y < .00004 && velo.y > -.00004){
			velo.y = 0;
		}
		if (velo.z < .00004 && velo.z > -.00004){
			velo.z = 0;
		}
		
		return velo;
	}else{
		return v;
	}
}

bool PhysicsManager::checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result)
{
	//std::cout << "We are checking a collision! \n";
	return node1.getCollider()->getCollision(*(node2.getCollider()), result);
}

void PhysicsManager::giveImpulse(Vector3f f, float dt, Ball& b){
    a = Vector3f(f.x/b.getMass(),f.y/b.getMass(),f.z/b.getMass());
    
    Vector3f v = Vector3f(b.getV().x + (a.x * dt),
                 0,
                 b.getV().z + (a.z * dt));
    
    b.setV(v);
}