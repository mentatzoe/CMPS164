#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#include <SDL.h>
#endif

#include <iostream>
#include "FileParser.h"
#include "LevelCreator.h"
#include "openglUtil.h"

#ifndef M_PI    //if the pi is not defined in the cmath header file
#define M_PI 3.1415926535       //define it
#endif

//// GLOBALS ////

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const bool USE_VSYNC = 1;			// 1 On, 0 Off, -1 Late Swap Tearing
float cam[] = { 0, -5, -5 };
float loc[] = { 0, 0, 0 };
float FoV = 90;
float orbitY = 0.0;
float orbitZ = 0.0;
float orbitX = 0.0;
float lightPosition[4] = { 0, -3, 0, 1 };
float diffuseColour[4] = { 0.3, 0.3, 0.3, 1 };
float ambientColour[4] = { .01, .01, .01, 1 };
float specularColour[4] = { 0.5, 0.5, 0.5, 1 };

GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

// Game window
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

// Render Flag
bool gRenderQuad = true;

//// END OF GLOBALS ////

/// Forward Declarations /// 
bool initGL();

bool init() {
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL_Init has failed. Error code: " << SDL_GetError() << "\n";
		success = false;
	}
	else {
		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		// Create Window
		gWindow = SDL_CreateWindow(
			"Lolie 164: Assignment 2"		// Window name
			, SDL_WINDOWPOS_UNDEFINED		// Window X Position
			, SDL_WINDOWPOS_UNDEFINED		// Window Y Position
			, WINDOW_WIDTH					// Window Width
			, WINDOW_HEIGHT					// Window Height
			, SDL_WINDOW_OPENGL				// Uint32 flags
			| SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			std::cout << "SDL_CreateWindow has failed. SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}
		else {
			// Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL) {
				std::cout << "SDL_GL_CreateContext has failed. SDL Error: " << SDL_GetError() << "\n";
				success = false;
			}
			else {
				// Set Vertical Sync
				if (SDL_GL_SetSwapInterval(USE_VSYNC) < 0) {
					std::cout << "Warning: SDL_GL_SetSwapInterval has failed (Vsync). SDL Error: " << SDL_GetError() << "\n";
				}

				// Initialize GL
				if (!initGL()){
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL() {
	bool success = true;
	GLenum err = GL_NO_ERROR;

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "Failed to initialize OpenGL. Error: " << gluErrorString(err) << "\n";
		success = false;
	}

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "Failed to initialize OpenGL. Error: " << gluErrorString(err) << "\n";
		success = false;
	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Check for error
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "Failed to initialize OpenGL. Error: " << gluErrorString(err) << "\n";
		success = false;
	}


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	//Check for error
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "Failed to initialize OpenGL. Error: " << gluErrorString(err) << "\n";
		success = false;
	}

	return success;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

void handleCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FoV, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam[0], cam[1], cam[2], 0, 0, 0, 0, 0, 1);
}

void handleKeys(unsigned char key, int x, int y)
{
}

void update()
{
	//No per frame update needed
}

void render(Level lvl)
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	handleCamera();

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColour);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColour);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularColour);

	glPushMatrix();
	glRotatef(orbitY, 0.0, -1.0, 0.0);

	glPushMatrix();
	glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
	// Draw our light
	drawCube();
	glPopMatrix();

	std::vector<Tile> tiles = lvl.getTileList();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_mat);
	glColor4f(0.0, 1.0, 0.0, 1.0);

	glPushMatrix();
	glTranslatef(loc[0], loc[1], loc[2]);
	for (Tile &t : tiles){
		drawTile(t, .1);
	}
	

	glPushMatrix();
	Vector4f cup = lvl.getCup();
	Vector4f tee = lvl.getTee();
	//std::cout << "CUP: [" << cup.x << ", " << cup.y << ", " << cup.z << "]\n";
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(cup.x, cup.y, cup.z);
	glColor4f(0.0, 1.0, 1.0, 1.0);
	gluCylinder(quadratic, 0.1, 0.1, 0.5f, 3, 3);
	glPopMatrix();

	glPushMatrix();
	GLUquadricObj *quadratic2;
	quadratic2 = gluNewQuadric();
	//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(tee.x, tee.y, tee.z);
	glColor4f(0.0, 1.0, 1.0, 1.0);
	gluCylinder(quadratic2, 0.1, 0.1, 0.5f, 3, 3);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	SDL_GL_SwapWindow(gWindow);
}

int main(int argc, char* args[])
{
	FileParser fp;
	TokenList list = fp.tokenize(args[1]);
	LevelCreator lc;
	Level test = lc.createLevel(list);
	test.print();
	// Start SDL
	if (!init()) {
		system("pause");
		exit(0);
	}

	// Main Loop
	else {
		bool quit = false;
		while (!quit) {

			// Process Events
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				switch (e.type){
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym){
					case SDLK_LEFT:
						orbitY += 5;
						break;
					case SDLK_RIGHT:
						orbitY -= 5;
						break;
					case SDLK_UP:
						cam[1] -= 0.5;
						break;
					case SDLK_DOWN:
						cam[1] += 0.5;
						break;
					case SDLK_e:
						FoV += 5;
						break;
					case SDLK_q:
						FoV -= 5;
						break;
					case SDLK_w:
						loc[2] += .2;
						break;
					case SDLK_a:
						loc[0] -= .2;
						break;
					case SDLK_s:
						loc[2] -= .2;
						break;
					case SDLK_d:
						loc[0] += .2;
						break;
					case SDLK_r:
						loc[1] += .2;
						break;
					case SDLK_f:
						loc[1] -= .2;
						break;
					default:
						break;
					}
				}
			}
			// Draw
			render(test);
		}
	}

	// Free and close
	close();
	return 0;
}