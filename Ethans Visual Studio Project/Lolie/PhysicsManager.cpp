#include "PhysicsManager.h"
#include "Boundary.h"
#include "Tile.h"
#include "Cup.h"
#include "Tee.h"
#include "LineCollider.h"

const float MASS = 0.045f;
const float PI = 3.14159f;

Vector3f v_init, v;
Vector3f p_init, p;
Vector3f a(0, 0, 0);
Vector3f up(0, 1, 0);
Vector3f x(1, 0, 0);
Vector3f z(0, 0, 1);

bool sameSign(Vector3f a, Vector3f b){
    return (a.x < 0 == b.x < 0 )||( a.y < 0 == b.y < 0 )|| (a.z < 0 == b.z <0);
}


void PhysicsManager::update(float dt, Ball& b)
{
	//std::cout << "Ball pos = (" << b.getPosition().x << ", " << b.getPosition().y << ", " << b.getPosition().z << ")\n";

	// Declarations
	float timeToColPos, timeLeft, distA, distB, theta, phi;
	Vector3f v_init, p_init, p_new, p, colPos, tileNormal;
	SceneNode* parent = b.getParent();
	std::vector<SceneNode*> siblings = parent->getChildren();

	// Get initial position and velocity
	v_init = b.getV();
	p_init = b.getPosition();

	//// IF ON A SLOPE, CHANGE ACCELERATION TO ACCOUNT FOR SLOPE
	Tile* parentTile = static_cast<Tile*>(parent);
	tileNormal = parentTile->getNormals()[0];

	// THETA = Angle of inclination, PHI = Angle of tilt
	theta = calcIncline(tileNormal);
	phi = calcTilt(tileNormal);

	a = calcAcceleration(theta, phi);

	// Calculate new position
	p = getNextPosition(p_init, v_init, dt, a);

	// Set point B of linecollider to new point (gives us the line)	
	// Assuming A is already original position.
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
					b.setV(Vector3f(0, 0, 0));
					break;
				case SceneNode::Cup_t:
					//Cup* cup = static_cast<Cup*>(siblings[i]);
					break;
				case SceneNode::Ball_t:
					break;
				case SceneNode::Boundary_t:
					Boundary* bound = static_cast<Boundary*>(siblings[i]);

					std::cout << "Collided with a boundary!\n";
					
					// If we collide with a physical boundary
					if (bound->isPhysical()){
						Vector3f N = bound->getNormals()[1];
						Vector3f I = b.getV();

						// Calculate new reflected velocity
						float dotProductIN = N.x * -I.x + N.z * -I.z;
						Vector3f temp = Vector3f(2 * dotProductIN * N.x, 2 * dotProductIN * N.y, 2 * dotProductIN * N.z);
						Vector3f vReflected = Vector3f(temp.x + I.x, 0, temp.z + I.z);

						// Calculate time it takes to reach colPos
						distA = distanceNoY(p_init, p);
						distB = distanceNoY(p_init, colPos);
						timeToColPos = (distB * timeLeft) / distA;

						//std::cout << "distA = " << distA << ", distB = " << distB << "\n";
						//std::cout << "timeToColPos = " << timeToColPos << "\n";

						// Find remaining time
						timeLeft = timeLeft - timeToColPos;

						//std::cout << "colPos = (" << colPos.x << ", " << colPos.y << ", " << colPos.z << ")\n";
						//std::cout << "vReflected = (" << vReflected.x << ", " << vReflected.y << ", " << vReflected.z << ")\n";
						//std::cout << "dt = " << dt << ", timeLeft = " << timeLeft << "\n";

						// Find new line given initial position is colPos and new velocity/pos and new time
						p_new = getNextPosition(colPos, vReflected, timeLeft, a);

						//std::cout << "vReflected = (" << p_new.x << ", " << p_new.y << ", " << p_new.z << ")\n";

						// Print status
						//std::cout << "Before calc: \n";
						//std::cout << "     A - Position: (" << b.getPosition().x << ", " << b.getPosition().y << ", " << b.getPosition().z << ")\n";
						//std::cout << "     B - Position: (" << b.getCollider()->getB().x << ", " << b.getCollider()->getB().y << ", " << b.getCollider()->getB().z << ")\n";
						//std::cout << "     Velocity: (" << b.getV().x << ", " << b.getV().y << ", " << b.getV().z << ")\n";

						// Update the Ball
						b.setPosition(colPos);
						b.setV(vReflected);
						b.getCollider()->setA(colPos);
						b.getCollider()->setB(p_new);

						//std::cout << "After calc: \n";
						//std::cout << "     A - Position: (" << b.getPosition().x << ", " << b.getPosition().y << ", " << b.getPosition().z << ")\n";
						//std::cout << "     B - Position: (" << b.getCollider()->getB().x << ", " << b.getCollider()->getB().y << ", " << b.getCollider()->getB().z << ")\n";
						//std::cout << "     Velocity: (" << b.getV().x << ", " << b.getV().y << ", " << b.getV().z << ")\n";

						//system("pause");

						// Loop to see if anything has been collided with
						continue;

					// Else we collided with a region change boundary
					}
					else{

						std::cout << "Before calc: \n";
						std::cout << "     A - Position: (" << b.getPosition().x << ", " << b.getPosition().y << ", " << b.getPosition().z << ")\n";
						std::cout << "     B - Position: (" << b.getCollider()->getB().x << ", " << b.getCollider()->getB().y << ", " << b.getCollider()->getB().z << ")\n";
						std::cout << "     Velocity: (" << b.getV().x << ", " << b.getV().y << ", " << b.getV().z << ")\n";
						std::cout << "     Parent Tile: " << static_cast<Tile*>(b.getParent())->getTileID() << "\n";

						// Declarations
						std::vector<Vector3f> tileVerts = parentTile->getVerts();
						std::vector<Vector3f> upper(tileVerts.begin(), tileVerts.end() - parentTile->getNumSides());
						std::vector<Vector3f> boundVerts = bound->getVerts();
						std::vector<int> neighbors = parentTile->getNeighbors();

						//// RECALCULATE LINE
						// Calculate time it takes to reach colPos
						distA = distanceNoY(p_init, p);
						distB = distanceNoY(p_init, colPos);
						timeToColPos = (distB * timeLeft) / distA;

						// Find remaining time
						timeLeft = timeLeft - timeToColPos;

						// Update the Ball
						b.setPosition(colPos);
						b.getCollider()->setA(colPos);

						//// SET NEW PARENT
						// Iterate through list of tile's verts
						for (int i = 0; i < upper.size(); i++) {

							// Find the pair of verts that created the boundary
							if (boundVerts[0] == upper[i] && boundVerts[3] == upper[(i + 1) % upper.size()]) {

								// Now the correct tileID for ball is the neigh[i]
								SceneNode* level = parent->getParent();
								std::vector<SceneNode*> tiles = parent->getParent()->getChildren();

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

						// Recalculate A
						tileNormal = static_cast<Tile*>(b.getParent())->getNormals()[0];

						// THETA = Angle of inclination, PHI = Angle of tilt
						theta = calcIncline(tileNormal);
						phi = calcTilt(tileNormal);

						a = calcAcceleration(theta, phi);

						// Find new line given initial position is colPos and new time
						p = getNextPosition(colPos, b.getV(), timeLeft, a);

						// Update the new pos
						b.getCollider()->setB(p_new);

						std::cout << "After calc: \n";
						std::cout << "     A - Position: (" << b.getPosition().x << ", " << b.getPosition().y << ", " << b.getPosition().z << ")\n";
						std::cout << "     B - Position: (" << b.getCollider()->getB().x << ", " << b.getCollider()->getB().y << ", " << b.getCollider()->getB().z << ")\n";
						std::cout << "     Velocity: (" << b.getV().x << ", " << b.getV().y << ", " << b.getV().z << ")\n";
						std::cout << "     Parent Tile: " << static_cast<Tile*>(b.getParent())->getTileID() << "\n";

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
	b.setV(updateV(b.getV(), a, timeLeft));

	std::cout << "     Velocity: (" << b.getV().x << ", " << b.getV().y << ", " << b.getV().z << ")\n";

	std::cout << "=============================\n";
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

Vector3f PhysicsManager::calcAcceleration(float theta, float phi)
{
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

bool PhysicsManager::checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result)
{
	//std::cout << "We are checking a collision! \n";
	return node1.getCollider()->getCollision(*(node2.getCollider()), result);
}

void PhysicsManager::giveImpulse(Vector3f f, float dt, Ball& b){
    a = Vector3f(f.x/b.getMass(),f.y/b.getMass(),f.z/b.getMass());
    
    v = Vector3f(b.getV().x + (a.x * dt),
                 0,
                 b.getV().z + (a.z * dt));
    
    b.setV(v);
}