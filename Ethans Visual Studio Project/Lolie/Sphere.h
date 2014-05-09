#ifndef SPHERE_H
#define SPHERE_H

#include "Libraries.h"

class Sphere : Drawable
{
public:
	Sphere(float radius): stacks(8), slices(8), radius(radius) {}
	Sphere() : stacks(8), slices(8), radius(0.1) {}

	void draw();

	int stacks;
	int slices;
	float radius;
};

#endif /* SPHERE_H */