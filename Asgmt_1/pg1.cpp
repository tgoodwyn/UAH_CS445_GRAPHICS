/////////////////////////////////////////////////////////////////////         
// program1.cpp
//
// Tyler Goodwyn's programming assignment 1 in CS445-01.
// This program draws a line segment with vertices equally apart along the
// path of a sine wave that moves from the left edge of the window,
// to the top of the window, to the bottom of the window, and finally 
// to the right edge of the window. The user may press keys to increase
// or decrease the number of vertices used to create the wave.

// drawScene is the function that draws the sine wave using the current
// # of vertices. keyInput is the function that gets passed into the 
// glut event handler in order to change the current # of vertices
///////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

#define PI 3.14159265358979324

// Globals.
static float Y = 50.0; // starting Y-coordinate of wave.
static int numVertices = 5; // Number of vertices on circle.

// Drawing routine.
void drawScene(void)
{
	float x = 0; // horizontal vertex position
	float t = 0; // Angle parameter.
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINE_STRIP);
	for (i = 0; i < numVertices; ++i)
	{
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(x, sin(t) * 50 + Y, 0.0);
		x += 100 / (numVertices - 1);
		t += 2 * PI / (numVertices - 1);
	}
	glEnd();
	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case '+':
		numVertices++;
		glutPostRedisplay();
		break;
	case '-':
		if (numVertices > 3) numVertices--;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press +/- to increase/decrease the number of vertices on the sine wave." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(3, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Project 1");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}