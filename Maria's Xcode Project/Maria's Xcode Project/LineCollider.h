#include <iostream>
#include "Collider2D.h"

class LineCollider : public Collider2D{

public:
    LineCollider(Vector3f a, Vector3f b)
    : A(a)
    , B(b){}
    bool getCollision(Collider2D c); // Checks if there's been a collision
    Vector3f getCollisionPoint(Collider2D c); //Returns collision point
    Vector3f getA() {return A;};
    Vector3f getB() {return B;};
private:
    Vector3f A,B;
    double Dot(const Vector3f& a,const Vector3f& b)                        { return (a.x*b.x) + (a.y*b.y); }
    double PerpDot(const Vector3f& a,const Vector3f& b)                    { return (a.y*b.x) - (a.x*b.y); }
};


