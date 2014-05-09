#include <iostream>
#include "Collider2D.h"

class LineCollider : public Collider2D{

public:
    LineCollider(Vector3f a, Vector3f b)
    : A(a)
    , B(b){}
    bool getCollision(Collider2D c, Vector3f& result); // Checks if there's been a collision
    Vector3f getA() {return A;};
    Vector3f getB() {return B;};
    void setA(Vector3f va){A = va;};
    void setB(Vector3f vb){B = vb;};
private:
    Vector3f A,B;
};


