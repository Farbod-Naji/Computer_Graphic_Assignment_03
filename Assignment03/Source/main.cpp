/*******************************************************************
		   Hierarchical Multi-Part Model Example
********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gl/glut.h>
#include <iostream>
#include <utility>
#include <vector>
#include "helper/VECTOR3D.h"
//#include "QuadMesh.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>

#include "Classes/Level.h"

Level* testLevel;


const int vWidth = 650;    // Viewport width in pixels
const int vHeight = 500;    // Viewport height in pixels



// Light properties
GLfloat light_position0[] = { -4.0F, 8.0F, 8.0F, 1.0F };
GLfloat light_position1[] = {  4.0F, 8.0F, 8.0F, 1.0F };
GLfloat light_diffuse[]   = {  1.0F, 1.0F, 1.0F, 1.0F };
GLfloat light_specular[]  = {  1.0F, 1.0F, 1.0F, 1.0F };
GLfloat light_ambient[]   = {  0.2F, 0.2F, 0.2F, 1.0F };

// Mouse button
int currentButton;

// Default Mesh Size
int meshSize = 25;

// Prototypes for functions in this module
void initOpenGL(int w, int h);
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseMotionHandler(int xMouse, int yMouse);
void keyboard(unsigned char key, int x, int y);
void functionKeys(int key, int x, int y);

void update(int param);

// ----------------------------------------------

int main(int argc, char** argv)
{
	testLevel = new Level(1);


	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(vWidth, vHeight);
	glutInitWindowPosition(200, 30);
	glutCreateWindow("3D Hierarchical Example");

	// Initialize GL
	initOpenGL(vWidth, vHeight);

	// Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotionHandler);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(functionKeys);

	glutTimerFunc(10, update, 0);

	// Start event loop, never returns
	glutMainLoop();

	return 0;
}


// Set up OpenGL. For viewport and projection setup see reshape(). 
void initOpenGL(int w, int h)
{
	// Set up and enable lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);   // This second light is currently off

	// Other OpenGL setup
	glEnable(GL_DEPTH_TEST);   // Remove hidded surfaces
	glShadeModel(GL_SMOOTH);   // Use smooth shading, makes boundaries between polygons harder to see 
	glClearColor(0.4F, 0.4F, 0.4F, 0.0F);  // Color and depth for glClear
	glClearDepth(1.0f);
	glEnable(GL_NORMALIZE);    // Renormalize normal vectors 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   // Nicer perspective

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void update(int param) {
	testLevel->update(0.0f);
	//glutSwapBuffers();
	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}

// Callback, called whenever GLUT determines that the window should be redisplayed
// or glutPostRedisplay() has been called.
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// Create Viewing Matrix V
	// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
	gluLookAt(testLevel->cameraCenterPosition.x, testLevel->cameraCenterPosition.y, testLevel->cameraCenterPosition.z,
			  //0.0f, 0.0f, 0.0f,
			  //testLevel->cameraLookAt.x, testLevel->cameraLookAt.y, testLevel->cameraLookAt.z,
			  0.0f, 0.0f, 0.0f,
			  0.0f,	1.0f, 0.0f);

	//glTranslatef(-testLevel->cameraCenterPosition.x, -testLevel->cameraCenterPosition.y, -testLevel->cameraCenterPosition.z);


	glTranslatef(+testLevel->cameraCenterPosition.x, +testLevel->cameraCenterPosition.y, testLevel->cameraCenterPosition.z);

	glRotatef( testLevel->gun->gunRotation.x, 1.0, 0.0, 0.0);
	glRotatef(-testLevel->gun->gunRotation.y, 0.0, 1.0, 0.0);
	//glRotatef(-testLevel->gun->gunRotation.z, 0.0, 0.0, 1.0);
	
	glTranslatef(-testLevel->cameraCenterPosition.x, -testLevel->cameraCenterPosition.y, -testLevel->cameraCenterPosition.z);

	// Draw Object inside the 3D space
	glPushMatrix();
		testLevel->render();
	glPopMatrix();


	glutSwapBuffers();   // Double buffering, swap buffers
}

// Callback, called at initialization and whenever user resizes the window.
void reshape(int w, int h)
{
	// Set up viewport, projection, then change to modelview matrix mode - 
	// display function will then set up camera and do modeling transforms.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)w / h, 0.2, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
	gluLookAt(0.0, 6.0, 22.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

float temp = 0.0;
float* selectedJoint = &temp;


// Callback, handles input from the keyboard, non-arrow keys
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		break;
	case 'C':
		break;
	}
	glutPostRedisplay();   // Trigger a window redisplay
}


// Callback, handles input from the keyboard, function and arrow keys
void functionKeys(int key, int x, int y)
{
	// Help key
	if (key == GLUT_KEY_F1)
	{

	}

	else if (key == GLUT_KEY_UP)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
	{
		//testLevel->gun->gunTurnUp(1.0f);
	}
	else if (key == GLUT_KEY_DOWN)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
	{
		//testLevel->gun->gunTurnDown(1.0f);
	}
	else if (key == GLUT_KEY_RIGHT)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
	{
		//testLevel->gun->gunTurnRight(1.0f);
	}
	else if (key == GLUT_KEY_LEFT)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
	{
		//testLevel->gun->gunTurnLeft(1.0f);
	}
	// Do transformations with arrow keys
	//else if (...)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
	//{
	//}

	glutPostRedisplay();   // Trigger a window redisplay
}

int prev_xMouse, prev_yMouse;

// Mouse button callback - use only if you want to 
void mouse(int button, int state, int x, int y)
{
	currentButton = button;

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			prev_xMouse = x;
			prev_yMouse = y;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			;
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();   // Trigger a window redisplay
}

// Mouse motion callback - use only if you want to 
void mouseMotionHandler(int xMouse, int yMouse)
{
	float dt_x, dt_y;
	if (currentButton == GLUT_LEFT_BUTTON)
	{
		dt_x = xMouse - prev_xMouse;
		dt_y = yMouse - prev_yMouse;

		testLevel->gun->gunTurnX(-dt_y);
		testLevel->gun->gunTurnY(dt_x);


		prev_xMouse = xMouse;
		prev_yMouse = yMouse;
	}
	else {
		
	}

	glutPostRedisplay();   // Trigger a window redisplay
}

