#ifndef LIBRARIES_H
#define LIBRARIES_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#else
#include <GL/freeglut.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#endif

#include "Drawable.h"

#endif /* LIBRARIES_H */