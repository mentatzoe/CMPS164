#include <iostream>
#include "Collider2D.h"

class CircleCollider : public Collider2D{
    
public:
    CircleCollider(Vector3f c, float r)
    : center(c)
    , radius(r){}
    bool getCollision(Collider2D c); // Checks if there's been a collision
    Vector3f getCollisionPoint(Collider2D c); //Returns collision point
private:
    Vector3f center;
    float radius;
};