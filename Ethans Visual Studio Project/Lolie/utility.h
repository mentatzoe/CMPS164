#ifndef UTILITY_H
#define UTILITY_H

#include <math.h>
#include <vector>

class Vector3f
{
public:
	Vector3f() : x(0), y(0), z(0) {}
	Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

	float x, y, z;
};

class Vector4f
{
public:
	Vector4f() : x(0), y(0), z(0), w(0) {}
	Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	float x, y, z, w;
};

float dot(float *a, float *b);

float angle(float *a, float *b);

Vector3f cross(Vector3f a, Vector3f b);

Vector3f calcSurfaceNormal(std::vector<Vector3f> vertList);

Vector3f normalize(Vector3f orig);

#endif /* UTILITY_H */