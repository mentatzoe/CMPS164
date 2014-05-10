#include "PhysicsManager.h"
#include "Boundary.h"
#include "Tile.h"
#include "Cup.h"
#include "Tee.h"
#define MASS = 0.045f

Vector3f v_init, v;
Vector3f p_init, p;
Vector3f a = Vector3f(0, 0, 0);



void PhysicsManager::update(float dt, Ball& b)
{
	// Check collisions with sibling scenenodes
	SceneNode* parent = b.getParent();
	std::vector<SceneNode*> siblings = parent->getChildren();

	for (int i = 0; i < siblings.size(); i++) {
		Vector3f colPos;
		if ((*siblings[i]).getType() == SceneNode::Ball_t){
			i++;
			if (i == siblings.size()){
				continue;
			}
		}
		if (checkCollision(b, (*siblings[i]), colPos)){
			//std::cout << "There was a collision!\n";

			// SWITCH: If Tee/IfBound/If Cup
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

				if (bound->isPhysical()){
					std::cout << "We have collided with a physical Boundary\n";
					Vector3f N = Vector3f(-colPos.z, colPos.y, colPos.x);
					Vector3f I = b.getV();
					//R= 2*(-I dot N)*N + I
					float dotProductIN = N.x * I.x + N.z + I.z;
					Vector3f temp = Vector3f(2 * dotProductIN * N.x, 2 * dotProductIN * N.y, 2 * dotProductIN * N.z);
					Vector3f vReflected = Vector3f(temp.x + I.x, temp.y + I.y, temp.z + I.z);
					b.setV(vReflected);
				}
				else {
					std::cout << "We have collided with a tileChange Boundary\n";
					Tile* parentTile = static_cast<Tile*>(bound->getParent());

					// Iterate through list of tile's verts
					std::vector<Vector3f> tileVerts = parentTile->getVerts();
					std::vector<Vector3f> upper(tileVerts.begin(), tileVerts.end() - parentTile->getNumSides());
					std::vector<Vector3f> boundVerts = bound->getVerts();
					std::vector<int> neighbors = parentTile->getNeighbors();

					for (int i = 0; i < upper.size(); i++) {

						// find the pair of verts that created the boundary
						if (boundVerts[0] == upper[i] && boundVerts[3] == upper[(i + 1) % upper.size()]) {
							//std::cout << "We found the neighbor, it is: " << neighbors[i] << "\n";
							// now the correct tileID for ball is the neigh[i]
							SceneNode* level = parent->getParent();
							std::vector<SceneNode*> tiles = parent->getParent()->getChildren();
							//std::cout << "tiles.size() = " << tiles.size() << "\n";

							for (SceneNode* tile : tiles) {
								//std::cout << "going through tiles...\n";
								if (tile->getType() == SceneNode::Tile_t){
									Tile* curTile = static_cast<Tile*>(tile);
									if (curTile->getTileID() == neighbors[i]){
										//std::cout << "We found a matching ID\n";
										b.setParent(curTile);
										std::cout << "Ball's Parent was changed!\n";
									}
								}
							}
						}
					}
				}

				break;

			}

			
            //First we check if it's a boundary and if the boundary is a changing tile one
            //If it's a changing tile boundary, we update the ball's parent
            //NOT IMPLEMENTED YET!!
            
            //If not, we proceed to reflect the ball's direction
            //We need to get the normal of the plane, supposing that we always incide in a 90º angle (which is a lie, but still)
            //the components of the normal will be x' = -z, z'=+x
            
		}
    }
    //We always update the position, velocity and store them as initials
    //Get p_init and v_init from the ball
    v_init = b.getV();
    p_init = b.getPosition();
    
    //Check that a and v are opposite
    //NOT IMPLEMENTED YET!!
    
    //Calculate new velocity
    v = Vector3f(b.getV().x + (a.x * dt), b.getV().y + (a.y * dt), b.getV().z + (a.z * dt));
    //Calculate new position
    p = Vector3f(p_init.x + v_init.x*dt + 0.5*dt*dt*a.x,
                 p_init.y + v_init.y*dt + 0.5*dt*dt*a.y,
                 p_init.z + v_init.z*dt + 0.5*dt*dt*a.z);
    //Store new position and velocity in the ball
    b.setV(v);
    b.setPosition(p);
    //Update collider
    b.getCollider()->setA(p); //new origin point (current position)
    b.getCollider()->setB(Vector3f(p.x + v.x*dt + 0.5*dt*dt*a.x,
                                  p.y + v.y*dt + 0.5*dt*dt*a.y,
                                  p.z + v.z*dt + 0.5*dt*dt*a.z)); //new destiny point (position on the next step)

}

bool PhysicsManager::checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result)
{
	//std::cout << "We are checking a collision! \n";
	return node1.getCollider()->getCollision(*(node2.getCollider()), result);
}

void PhysicsManager::giveImpulse(Vector3f f, float dt, Ball& b){
    a = Vector3f(f.x/b.getMass(),f.y/b.getMass(),f.z/b.getMass());
    
    v = Vector3f(b.getV().x + (a.x * dt),
                 b.getV().y + (a.y * dt),
                 b.getV().z + (a.z * dt));
    
    b.setV(v);
}