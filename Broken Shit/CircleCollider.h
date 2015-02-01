#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <iostream>
#include "Collider2D.h"

class CircleCollider : public Collider2D{
    
public:
    CircleCollider(Vector3f c, float r)
    : center(c)
	, radius(r){
		setType(Circle_t);
	}
	Vector3f getCenter() { return center; }
	float getRadius() { return radius; }
    bool getCollision(Collider2D& c, Vector3f& result); // Checks if there's been a collision
private:
    Vector3f center;
    float radius;
};

#endif /*CIRCLECOLLIDER_H*/