#ifndef UTILITY_H
#define UTILITY_H

#include <math.h>
#include <vector>

class Vector3f
{
public:
	Vector3f() : x(0), y(0), z(0) {}
	Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3f operator+(const Vector3f& other) {
		return Vector3f(x + other.x, y + other.y, z + other.z);
	}

	Vector3f operator-(const Vector3f& other) {
		return Vector3f(x - other.x, y - other.y, z - other.z);
	}

	Vector3f operator*(const Vector3f& other) {
		return Vector3f(x * other.x, y * other.y, z * other.z);
	}

	Vector3f operator*(const float& scalar) {
		return Vector3f(x * scalar, y * scalar, z * scalar);
	}

	bool operator==(const Vector3f& other) {
		if (x == other.x && y == other.y && z == other.z)
			return true;
		else
			return false;
	}

	float x, y, z;
};

class Vector4f
{
public:
	Vector4f() : x(0), y(0), z(0), w(0) {}
	Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	float x, y, z, w;
};

float dot(Vector3f a, Vector3f b);

float angle(float *a, float *b);

float magnitude(Vector3f a);

float distance(Vector3f posA, Vector3f posB);

float distanceNoY(Vector3f posA, Vector3f posB);

Vector3f cross(Vector3f a, Vector3f b);

Vector3f calcSurfaceNormal(std::vector<Vector3f> vertList);

Vector3f normalize(Vector3f orig);

struct Cylinder {
	float radius, height, slices, stacks;
};

struct Sphere {
	int stacks, slices;
	float radius;
};

struct Ray {
	Vector3f origin;
	Vector3f direction;
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
		return Point(xval - other.xval, yval - other.yval);
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


#endif /* UTILITY_H */