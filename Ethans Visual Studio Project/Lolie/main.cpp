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
#include "Camera.h"

#ifndef M_PI    //if the pi is not defined in the cmath header file
#define M_PI 3.1415926535       //define it
#endif

//// GLOBALS ////

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const bool USE_VSYNC = 1;			// 1 On, 0 Off, -1 Late Swap Tearing
bool quit = false;
float FoV = 90;
float lightPosition[4] = { 0, 5, 0, 1 };
float diffuseColour[4] = { .5, .5, .5, 1 };
float ambientColour[4] = { 0, 0, 0, 1 };
float specularColour[4] = { .1, .1, .1, 1 };

GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0, 0, 0, 1 };

// Game window
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

// Render Flag
bool gRenderQuad = true;

// Our Rendering Camera
Camera camera;
int cameraProfile = 0;

//// END OF GLOBALS ////

/// Forward Declarations /// 
bool initGL(int argc, char* args[]);

bool init(int argc, char* args[]) {
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
				if (!initGL(argc, args)){
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL(int argc, char* args[]) {
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
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//Check for error
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "Failed to initialize OpenGL. Error: " << gluErrorString(err) << "\n";
		success = false;
	}

	glutInit(&argc, args);

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
	gluLookAt(0, 5, 0, 0, 0, 0, 0, 1, 0);
}

void freeLookControls()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type){
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym){
			case SDLK_LEFT:
				camera.rotateY(5.0);
				break;
			case SDLK_RIGHT:
				camera.rotateY(-5.0);
				break;
			case SDLK_UP:
				camera.rotateX(5.0);
				break;
			case SDLK_DOWN:
				camera.rotateX(-5.0);
				break;
			case SDLK_w:
				camera.moveForwards(-0.1);
				break;
			case SDLK_a:
				camera.strafeRight(-0.1);
				break;
			case SDLK_s:
				camera.moveForwards(0.1);
				break;
			case SDLK_d:
				camera.strafeRight(0.1);
				break;
			case SDLK_r:
				camera.move(Vector3f(0, .3, 0));
				break;
			case SDLK_f:
				camera.move(Vector3f(0, -.3, 0));
				break;
			case SDLK_x:
				// Switch to TopDown profile
				cameraProfile = 1;
				camera.setTopDown();
				break;
			default:
				break;
			}
		}
	}
}

void topDownControls()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type){
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym){
			case SDLK_a:
				camera.move(Vector3f(-.2, 0, 0));
				break;
			case SDLK_d:
				camera.move(Vector3f(.2, 0, 0));
				break;
			case SDLK_w:
				camera.move(Vector3f(0, 0, -.2));
				break;
			case SDLK_s:
				camera.move(Vector3f(0, 0, .2));
				break;
			case SDLK_r:
				camera.move(Vector3f(0, .3, 0));
				break;
			case SDLK_f:
				camera.move(Vector3f(0, -.3, 0));
				break;
			case SDLK_z:
				// Switch to FreeLook profile
				cameraProfile = 0;
				camera.setFreeLook();
				break;
			default:
				break;
			}
		}
	}
}

void handleEvents()
{
	if (cameraProfile == 0){
		freeLookControls();
	}
	else if (cameraProfile == 1){
		topDownControls();
	}
}

void update(Level lvl)
{
	//No per frame update needed
	lvl.update(0.0);
}

void draw(Level lvl)
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//handleCamera();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FoV, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera.render();

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColour);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColour);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularColour);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_emission);

	glPushMatrix();

	lvl.draw();

	glPopMatrix();

	SDL_GL_SwapWindow(gWindow);
}

int main(int argc, char* args[])
{
	FileParser fp;
	TokenList list = fp.tokenize(args[1]);
	LevelCreator lc;
	Level test = lc.createLevel(list);

	// Start SDL
	if (!init(argc, args)) {
		system("pause");
		exit(0);
	}

	// Main Loop
	else {
		Uint32 start_time_ms = SDL_GetTicks();
		Uint32 prev_time = start_time_ms;
		Uint32 curr_time;
		float delta_time = .02;
		float physics_lag_time = 0.0;

		while (!quit) {
			// Update game time
			curr_time = SDL_GetTicks() - start_time_ms;

			// Calc time since last update
			physics_lag_time += curr_time - prev_time;

			/*while (physics_lag_time > delta_time) {
				// doPhysicsSimulaton(dt);
				physics_lag_time -= delta_time;
			}*/


			// Process Events
			handleEvents();
			// Update
			update(test);
			// Draw
			draw(test);

			prev_time = curr_time;
		}
	}

	// Free and close
	close();
	return 0;
}