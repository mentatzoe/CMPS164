#include "CircleCollider.h"

Vector3f CircleCollider::getCollisionPoint(Collider2D col){
    //Pseudocode for circle collision
    Point p1 = Point(col.getA().x-center.x, col.getA().z-center.z);
    Point p2 = Point(col.getB().x-center.x, col.getB().z-center.z);

    Point P2MinusP1 = Point(p2.x() - p1.x(), p2.y() - p1.y());
    
//P2MinusP1 = LocalP2 – LocalP1
//
    
    float a = (P2MinusP1.x()) * (P2MinusP1.x()) + (P2MinusP1.y()) * (P2MinusP1.y());
    float b = 2 * ((P2MinusP1.x() * p1.x()) + (P2MinusP1.y() * p1.y()));
    float c = (p1.x() * p1.x()) + (p1.y() * p1.y()) - (radius * radius);
    float delta = b * b - (4 * a * c);
    if (delta < 0)  // No intersection
        return Vector3f(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    else if (delta == 0){ // One intersection
        float u = -b / (2 * a);
        Point temp = Point(u* P2MinusP1.x(), u*P2MinusP1.y());
        //return col.getA() + (u * P2MinusP1)
        return Vector3f(col.getA().x + temp.x(), 0, col.getA().y + temp.y());
    }
/* Use LineP1 instead of LocalP1 because we want our answer in global
// space, not the circle's local space */
    else if (delta > 0){ // Two intersections
        float SquareRootDelta = sqrt(delta);
        float u1 = (-b + SquareRootDelta) / (2 * a);
        float u2 = (-b - SquareRootDelta) / (2 * a);

        //return { LineP1 + (u1 * P2MinusP1) ; LineP1 + (u2 * P2MinusP1)}
    }
    return Vector3f(0,0,0);
}