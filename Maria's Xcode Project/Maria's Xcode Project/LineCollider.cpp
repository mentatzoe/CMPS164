#include "LineCollider.h"

bool LineCollider::getCollision(Collider2D c, Vector3f& result){
    //return intersection(getA(), getB(), c.getA(), c.getB());
    // Store the values for fast access and easy
    // equations-to-code conversion
    float x1 = getA().x, x2 = getB().x, x3 = c.getA().x, x4 = c.getB().x;
    float y1 = getA().z, y2 = getB().z, y3 = c.getA().z, y4 = c.getB().z;
    
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
    
    result.x = x;
    result.z = y;
    
    return true;
};