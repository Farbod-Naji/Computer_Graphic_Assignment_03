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
#include "VECTOR3D.h"
#include "QuadMesh.h"


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

// A flat open mesh
QuadMesh* groundMesh = NULL;

// Structure defining a bounding box, currently unused
typedef struct BoundingBox {
	VECTOR3D min;
	VECTOR3D max;
} BBox;

// Default Mesh Size
int meshSize = 16;

// Prototypes for functions in this module
void initOpenGL(int w, int h);
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseMotionHandler(int xMouse, int yMouse);
void keyboard(unsigned char key, int x, int y);
void functionKeys(int key, int x, int y);

// ----------------------------------------------

/*
GLUT_BITMAP_8_BY_13 | GLUT_BITMAP_9_BY_15 | GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24 |GLUT_BITMAP_HELVETICA_10 | GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18
*/

void MyTranslatef(float TranslateX, float TranslateY, float TranslateZ) {
	const GLfloat m[] = {  1.0,  0.0,  0.0,   0.0f,
						   0.0,  1.0,  0.0,   0.0f,
						   0.0,  0.0,  1.0,   0.0f,
						   TranslateX,  TranslateY,  TranslateZ,   1.0 };
	glMultMatrixf(m);
}

void MyRotatef(float angle, float axisX, float axisY, float axisZ) {
	float allAxis = axisX + axisY + axisZ;
	axisX /= allAxis;
	axisY /= allAxis;
	axisZ /= allAxis;

	// rotate in X
	if (axisX != 0.0f) {
		float rotationX = angle * axisX;
		rotationX *= (3.14f / 180.0f);
		const GLfloat m1[] = { 1.0f,			   0.0f,			  0.0f,   0.0f,
								0.0f,	cosf(rotationX),   sinf(rotationX),   0.0f,
								0.0f,  -sinf(rotationX),   cosf(rotationX),   0.0f,
								0.0f,			   0.0f,			  0.0f,   1.0f };
		glMultMatrixf(m1);
	}

	// rotate in Y
	if (axisY != 0.0f) {
		float rotationY = angle * axisY;
		rotationY *= (3.14f / 180.0f);
		const GLfloat m2[] = {   cosf(rotationY), 0.0f,  -sinf(rotationY),   0.0f,
											0.0f, 1.0f, 	   	     0.0f,   0.0f,
								 sinf(rotationY), 0.0f,   cosf(rotationY),   0.0f,
											0.0f, 0.0f, 		     0.0f,   1.0f };
		glMultMatrixf(m2);
	}

	// rotate in Z
	if (axisZ != 0.0f) {
		float rotationZ = angle * axisZ;
		rotationZ *= (3.14f / 180.0f);

		const GLfloat m3[] = {  cosf(rotationZ),  sinf(rotationZ),   0.0f,   0.0f,
							   -sinf(rotationZ),  cosf(rotationZ),   0.0f,   0.0f,
										   0.0f,		     0.0f,   1.0f,   0.0f,
										   0.0f,		     0.0f,   0.0f,   1.0f };
		glMultMatrixf(m3);
	}
}

void MyScalef(float scaleX, float scaleY, float scaleZ) {
	const GLfloat n[] = { scaleX,   0.0,   0.0,   0.0,
							 0.0, scaleY,   0.0,   0.0,
							 0.0,   0.0, scaleZ,   0.0,
							 0.0,   0.0,   0.0,   1.0 };
	glMultMatrixf(n);
}


void drawFilledCylinder() {
	glPushMatrix();
		MyRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		gluDisk(gluNewQuadric(), 0.0, 1.0, 20, 10);
	glPopMatrix();

	glPushMatrix();
		MyTranslatef(0.0f, 0.0f, 1.0f);
		gluDisk(gluNewQuadric(), 0.0, 1.0, 20, 10);
	glPopMatrix();

	glPushMatrix();
		gluCylinder(gluNewQuadric(), 1.0, 1.0, 1.0, 20, 10);
	glPopMatrix();
}

// ----------------------------------------------

int main(int argc, char** argv)
{
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


	// Other initializatuion
	// Set up ground quad mesh
	VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
	VECTOR3D dir1v = VECTOR3D(1.0f, 0.0f, 0.0f);
	VECTOR3D dir2v = VECTOR3D(0.0f, 0.0f, -1.0f);
	groundMesh = new QuadMesh(meshSize, 32.0);
	groundMesh->InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v);

	VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
	VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
	VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
	float shininess = 0.2f;
	groundMesh->SetMaterial(ambient, diffuse, specular, shininess);

}


// Callback, called whenever GLUT determines that the window should be redisplayed
// or glutPostRedisplay() has been called.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// Create Viewing Matrix V
	// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
	gluLookAt(0.0, 0.0, 32.0, 0.0, -6.0, 0.0, 0.0, 1.0, 0.0);

	// Draw Object inside the 3D space
	glPushMatrix();

		// Draw ground
		glPushMatrix();
			MyTranslatef(0.0, -20.0, 0.0);
			groundMesh->DrawMesh(meshSize);
		glPopMatrix();

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
	}
	else if (key == GLUT_KEY_DOWN)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
	{
	}
	else if (key == GLUT_KEY_RIGHT)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
	{
	}
	else if (key == GLUT_KEY_LEFT)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
	{
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
	if (currentButton == GLUT_LEFT_BUTTON)
	{
		//dt_x += xMouse - prev_xMouse;
		//dt_y += yMouse - prev_yMouse;

		prev_xMouse = xMouse;
		prev_yMouse = yMouse;
	}
	else {
		
	}

	glutPostRedisplay();   // Trigger a window redisplay
}

