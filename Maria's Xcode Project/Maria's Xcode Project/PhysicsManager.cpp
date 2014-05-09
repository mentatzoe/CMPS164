#include "PhysicsManager.h"

Vector3f v_init, v;
Vector3f p_init, p;
Vector3f a = Vector3f(-9.8, 0, -9.8);

void PhysicsManager::update(float dt, Ball& b)
{
	// Check collisions with sibling scenenodes
	SceneNode* parent = b.getParent();
	std::vector<SceneNode*> siblings = parent->getChildren();

	for (int i = 0; i < siblings.size(); i++) {
		Vector3f colPos;
		if (checkCollision(b, (*siblings[i]), colPos)){
			// There was a collision at point colPos
            
			// Do stuff
		}
        //We always update the position, velocity and store them as initials
        //Get p_init and v_init from the ball
        v_init = b.getV();
        p_init = b.getPosition();
        //Check that a and v are opposite
        //NOT IMPLEMENTED YET
        
        //Calculate new velocity
        v = Vector3f(b.getV().x + (a.x * dt), b.getV().y + (a.y * dt), b.getV().z + (a.z * dt));
        //Calculate new position
        p = Vector3f(p_init.x + v_init.x*dt + 0.5*dt*dt*a.x,
                     p_init.y + v_init.y*dt + 0.5*dt*dt*a.y,
                     p_init.z + v_init.z*dt + 0.5*dt*dt*a.z);
        //Store new position and velocity in the ball
        b.setV(v);
        b.setPosition(p);
        
	}
}

bool PhysicsManager::checkCollision(SceneNode& node1, SceneNode& node2, Vector3f& result)
{
	return node1.getCollider().getCollision(node2.getCollider(), result);
}

void PhysicsManager::giveImpulse(Vector3f f, float dt, Ball& b){
    
    a = Vector3f(f.x/b.getMass(),
                 f.y/b.getMass(),
                 f.z/b.getMass());
    
    v = Vector3f(b.getV().x + (a.x * dt),
                 b.getV().y + (a.y * dt),
                 b.getV().z + (a.z * dt));
    
    b.setV(v);
}