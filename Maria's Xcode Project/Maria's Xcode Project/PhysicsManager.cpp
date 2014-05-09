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
            //First we check if it's a boundary and if the boundary is a changing tile one
            //WELL, WE'RE ASSUMING THAT IT'S A BOUNDARY
            Boundary bound = static_cast<Boundary>(*siblings[i]);
            if (bound.isPhysical()){
                //If it's a physical boundary, we proceed to reflect the ball's direction
                //We need to get the normal of the plane, supposing that we always incide in a 90º angle (which is a lie, but still)
                //the components of the normal will be x' = -z, z'=+x
                
                Vector3f N = Vector3f(-colPos.z, colPos.y, +colPos.x);
                Vector3f I = b.getV();
                //R= 2*(-I dot N)*N + I
                float dotProductIN = N.x * I.x + N.z + I.z;
                Vector3f temp = Vector3f(2*dotProductIN * N.x, 2*dotProductIN * N.y, 2*dotProductIN * N.z);
                Vector3f vReflected = Vector3f(temp.x+I.x, temp.y+I.y, temp.z+I.z);
                b.setV(vReflected);
            } else {
                //If it's a changing tile boundary, we update the ball's parent
                b.setParent(bound.getParent());
            }
           
		}
        //We always update the position, velocity and store them as initials
        //Get p_init and v_init from the ball
        v_init = b.getV();
        p_init = b.getPosition();
        
        //Check that a and v are opposite
        //NOT IMPLEMENTED YET!! (but we shouldn't need it right now)
        
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
        b.getCollider().setA(p); //new origin point (current position)
        b.getCollider().setB(Vector3f(p.x + v.x*dt + 0.5*dt*dt*a.x,
                                      p.y + v.y*dt + 0.5*dt*dt*a.y,
                                      p.z + v.z*dt + 0.5*dt*dt*a.z)); //new destiny point (position on the next step)
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