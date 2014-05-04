#include "Cup.h"

Cup::Cup(int id, Vector3f pos)
: pos(pos)
, tileID(id)
{
	color = { 0.0, 0.0, 0.0, 1.0 };
	dimensions.height = .05;
	dimensions.slices = 7;
	dimensions.radius = .06; 
	dimensions.stacks = 3;
}