#include "Tee.h"

Tee::Tee(int id, Vector3f pos)
: pos(pos)
, tileID(id)
{
	color = { 0.0, 1.0, 1.0, 1.0 };
	dimensions.height = .05;
	dimensions.slices = 7;
	dimensions.radius = .02;
	dimensions.stacks = 3;
}