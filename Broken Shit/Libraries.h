#ifndef LIBRARIES_H
#define LIBRARIES_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <SDL2/SDL.h>
#else
#include <gl/freeglut.h>
#include <SDL.h>
#endif

#include "Drawable.h"

#endif /* LIBRARIES_H */