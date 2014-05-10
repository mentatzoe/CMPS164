#ifndef LINECOLLIDER_H
#define LINECOLLIDER_H

#include <iostream>
#include "Collider2D.h"

class LineCollider : public Collider2D{

public:
	LineCollider(Vector3f a, Vector3f b)
	{
		setA(a); setB(b);
	}
    bool getCollision(Collider2D& c, Vector3f& result); // Checks if there's been a collision
private:
};

#endif /*LINECOLLIDER_H*/

