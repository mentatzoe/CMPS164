#include "CircleCollider.h"



bool CircleCollider::getCollision(Collider2D& col, Vector3f& result){
    //Pseudocode for circle collision
    //getting local points
    Point p1 = Point(col.getA().x-center.x, col.getA().z-center.z);
    Point p2 = Point(col.getB().x-center.x, col.getB().z-center.z);

    Point P2MinusP1 = Point(p2.x() - p1.x(), p2.y() - p1.y());
    
    float a = (P2MinusP1.x()) * (P2MinusP1.x()) + (P2MinusP1.y()) * (P2MinusP1.y());
    float b = 2 * ((P2MinusP1.x() * p1.x()) + (P2MinusP1.y() * p1.y()));
    float c = (p1.x() * p1.x()) + (p1.y() * p1.y()) - (radius * radius);
    float delta = b * b - (4 * a * c);
    if (delta < 0)  // No intersection
        return false;
    else if (delta == 0){ // One intersection
        float u = -b / (2 * a);
        Point temp = Point(u* P2MinusP1.x(), u*P2MinusP1.y());
        //return col.getA() + (u * P2MinusP1)
        result.x = col.getA().x + temp.x();
        result.y = 0;
        result.z = col.getA().y + temp.y();
        return true;
    }
    else if (delta > 0){ // Two intersections, which is never gonna happen in our scenario
        float SquareRootDelta = sqrt(delta);
        float u1 = (-b + SquareRootDelta) / (2 * a);
        //float u2 = (-b - SquareRootDelta) / (2 * a);

        //return { LineP1 + (u1 * P2MinusP1) ; LineP1 + (u2 * P2MinusP1)}
        result.x = p1.x() + (u1 * P2MinusP1.x());
        result.y = 0;
        result.z = p1.y() + (u1 * P2MinusP1.y());
        return true;
    }
    return false;
}