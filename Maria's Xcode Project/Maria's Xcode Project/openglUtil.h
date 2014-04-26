#ifndef OPENGLUTIL_H
#define OPENGLUTIL_H

#include "utility.h"
#include "Tile.h"

void drawCube();

void drawTile(Tile tile, float thickness);

void drawBoundary(Vector3f v1, Vector3f v2, float H);

#endif /* OPENGLUTILITY_H */