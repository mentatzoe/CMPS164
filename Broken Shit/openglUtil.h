#ifndef OPENGLUTIL_H
#define OPENGLUTIL_H

#include "utility.h"
#include "Tile.h"
#include "Cup.h"
#include "Tee.h"

void drawCube();

void drawTile(Tile tile);

void drawTee(Tee tee);

void drawCup(Cup cup);

void drawBoundary(Vector3f v1, Vector3f v2, float H);

#endif /* OPENGLUTILITY_H */