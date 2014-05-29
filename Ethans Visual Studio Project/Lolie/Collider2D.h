#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include <iostream>
#include "utility.h"

class Collider2D
{
public:
	virtual bool getCollision(Collider2D& c, Vector3f& result) = 0;
    Vector3f getA() {return A;};
    Vector3f getB() {return B;};
    void setA(Vector3f va){A = va;};
    void setB(Vector3f vb){B = vb;};
	friend class SceneNode;
protected:
	Collider2D() {};
	Vector3f A, B;
};

#endif /*COLLIDER2D_H*/