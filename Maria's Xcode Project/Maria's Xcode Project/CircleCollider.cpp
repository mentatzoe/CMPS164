#include "CircleCollider.h"

Vector3f CircleCollider::getCollisionPoint(Collider2D c){
    //Pseudocode for circle collision
    
//LocalP1 = LineP1 – CircleCentre
//LocalP2 = LineP2 – CircleCentre
////
//P2MinusP1 = LocalP2 – LocalP1
//
//a = (P2MinusP1.X) * (P2MinusP1.X) + (P2MinusP1.Y) * (P2MinusP1.Y)
//b = 2 * ((P2MinusP1.X * LocalP1.X) + (P2MinusP1.Y * LocalP1.Y))
//c = (LocalP1.X * LocalP1.X) + (LocalP1.Y * LocalP1.Y) – (Radius * Radius)
//delta = b * b – (4 * a * c)
//if (delta < 0) // No intersection
//return null;
//else if (delta == 0) // One intersection
//u = -b / (2 * a)
//return LineP1 + (u * P2MinusP1)
///* Use LineP1 instead of LocalP1 because we want our answer in global
// space, not the circle's local space */
//else if (delta > 0) // Two intersections
//SquareRootDelta = sqrt(delta)
//
//u1 = (-b + SquareRootDelta) / (2 * a)
//u2 = (-b - SquareRootDelta) / (2 * a)
//
//return { LineP1 + (u1 * P2MinusP1) ; LineP1 + (u2 * P2MinusP1)}
    return Vector3f(0,0,0);
}