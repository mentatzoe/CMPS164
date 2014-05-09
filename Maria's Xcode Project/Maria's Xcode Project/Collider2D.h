#include <iostream>
#include "openglUtil.h"

class Collider2D
{
public:
    Vector3f A, B;
    virtual bool getCollision(Collider2D c);
    virtual Vector3f getA() {return A;};
    virtual Vector3f getB() {return B;};
};
