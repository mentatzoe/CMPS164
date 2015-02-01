#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include <iostream>
#include "utility.h"

class Collider2D
{
public:
	// Class Categories
	enum Type {
		Circle_t,
		Line_t,
	};

	// Getters / Setters
	virtual bool getCollision(Collider2D& c, Vector3f& result) = 0;
	Vector3f getA() { return A; }
	Vector3f getB() { return B; }
	Type getType() { return mType; }
	void setType(Type type) { mType = type; }
    void setA(Vector3f va){A = va;}
    void setB(Vector3f vb){B = vb;}
	friend class SceneNode;
protected:
	// Member variables
	Vector3f A, B;
	Type mType;

	// Abstract class
	Collider2D() {};
};

#endif /*COLLIDER2D_H*/