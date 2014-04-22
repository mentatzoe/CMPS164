//
//  main.cpp
//  Maria's Xcode Project
//
//  Created by Maria Lopez Latorre on 15/04/14.
//  Copyright (c) 2014 CMPS 164 Game Engines. All rights reserved.
//

#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Tile.h"
#include "LevelCreator.h"
#include "Level.h"
#include "FileParser.h"
#include <iostream>

using namespace std;

double rotate_y=0;
double rotate_x=0;
bool levelLoaded = false;
string filename = "";
Level l;
// angle of rotation for the camera direction
float angle=0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

//Called when a key is pressed
void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 0.1f;
    printf("%f",x);
    printf("%f",z);
	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}

    
    //glutPostRedisplay();
}

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}
//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
//	gluPerspective(110.0,                  //The camera angle
//				   (double)w / (double)h, //The width-to-height ratio
//				   1.0,                   //The near z clipping coordinate
//				   200.0);                //The far z clipping coordinate
}



// SCENE FRAWING
void drawScene() {
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity();
	// Set the camera
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(1, 1, -1,
              15, 10, 0,
              0, 0, 1);
    glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 1.0 );
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
    
    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
    
    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    
    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
    
    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    
    
    std::vector<Tile> tiles = l.getTileList();
    for (Tile &t : tiles){
        glBegin(GL_QUADS);
        glColor4f(0.0, 1.0, 0.0, 1.0);
        for (Vector3f &v : t.getVerts()){
            glVertex3f(v.x, v.y, v.z);
        }
        glEnd();
    }
    
    glFlush();
    
    angle+=0.1f;
    glutSwapBuffers(); //Send the 3D scene to the screen
    
}


int main(int argc, char** argv)
{
    //Find the level
    if (argv[1]==NULL){
        printf ("No file indicated ");
        exit (EXIT_FAILURE);
    } else {
        filename = argv[1];
    }
    
    FileParser fp = FileParser();
    LevelCreator lc = LevelCreator();

    
    //Load the level
    l = lc.createLevel(fp.tokenize(filename));
    
    //If the structures are available
    levelLoaded = true;
    
	//Initialize GLUT
	if (levelLoaded){
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(400, 400); //Set the window size
        //Create the window
        glutCreateWindow("MiniGolf");
        initRendering(); //Initialize rendering
        //Set handler functions for drawing, keypresses, and window resizes
        glutDisplayFunc(drawScene);
        glutSpecialFunc(processSpecialKeys);
        glutReshapeFunc(handleResize);
        glutMainLoop(); //Start the main loop
    }
	return 0;
}

