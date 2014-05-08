#include "Sphere.h"

void Sphere::draw() 
{
	glutSolidSphere(radius, slices, stacks);
}