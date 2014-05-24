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



// Class to represent points.
class Point {
private:
	double xval, yval;
public:
	// Constructor uses default arguments to allow calling with zero, one,
	// or two values.
	Point(double x = 0.0, double y = 0.0) {
		xval = x;
		yval = y;
	}

	// Extractors.
	double x() { return xval; }
	double y() { return yval; }

	// Distance to another point.  Pythagorean thm.
	double dist(Point other) {
		double xd = xval - other.xval;
		double yd = yval - other.yval;
		return sqrt(xd*xd + yd*yd);
	}

	// Add or subtract two points.
	Point add(Point b)
	{
		return Point(xval + b.xval, yval + b.yval);
	}
	Point sub(Point b)
	{
		return Point(xval - b.xval, yval - b.yval);
	}

    Point operator-(const Point& other){
        return Point(xval - other.xval, yval-other.yval);
    }

	Point operator*(const Point& other){
		return Point(xval * other.xval, yval * other.yval);
	}

	Point operator+(const Point& other){
		return Point(xval + other.xval, yval + other.yval);
	}
	// Move the existing point.
	void move(double a, double b)
	{
		xval += a;
		yval += b;
	}
};

#endif /*COLLIDER2D_H*/