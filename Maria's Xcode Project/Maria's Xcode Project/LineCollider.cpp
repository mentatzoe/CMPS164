#include "LineCollider.h"

float collisionX, collisionZ;

bool intersection(Vector3f p1, Vector3f p2, Vector3f p3, Vector3f p4);

bool LineCollider::getCollision(Collider2D c){
    return intersection(getA(), getB(), c.getA(), c.getB());
};


bool intersection(Vector3f p1, Vector3f p2, Vector3f p3, Vector3f p4) {
    // Store the values for fast access and easy
    // equations-to-code conversion
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.z, y2 = p2.z, y3 = p3.z, y4 = p4.z;
    
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return false;
    
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
    
    // Check if the x and y coordinates are within both lines
    if ( x < fmin(x1, x2) || x > fmax(x1, x2) ||
        x < fmin(x3, x4) || x > fmax(x3, x4) ) return false;
    if ( y < fmin(y1, y2) || y > fmax(y1, y2) ||
        y < fmin(y3, y4) || y > fmax(y3, y4) ) return false;
    
    collisionX = x;
    collisionZ = y;
    
    return true;
};

Vector3f LineCollider::getCollisionPoint(Collider2D c){
    return Vector3f(collisionX, 0, collisionZ);
};