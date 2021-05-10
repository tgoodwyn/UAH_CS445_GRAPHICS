///////////////////////////////////////////////////////////////
// Tyler Goodwyn - CS 445: Assignment 3
//
//This program is a simple drawing application.
//It allows the user to select from one of 4 brushes
//that can draw a simple primitive to the screen
//using a perspective projection.
//
//The major functions are the drawShapes function that draws the shapes that the user
//has chosen to add to the screen and the drawName function that posts the current 
//brush to the screen.
// 
// It has one class: the Shape class, and a global vector that holds all instantiated
// shapes.
///////////////////////////////////////////////////////////////

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static float Xvalue = 0.0, Yvalue = 0.0; 
static int current_brush_index = 0;
static long font = (long)GLUT_BITMAP_TIMES_ROMAN_24; // Font selection.

// Function for writing text to the screen
void writeBitmapString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void drawName(int bName)
{
	std::string text = "";
	switch (bName)
	{
	case 3:
		text="Square\0";
		break;
	case 2:
		text = "Triangle\0";
		break;
	case 1:
		text = "Sphere\0";
		break;
	case 0:
		text = "Cube\0";
		break;
	}
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos3f(-420.0, -420.0, -50.0);
	writeBitmapString((void*)font, (char*) text.c_str());
	glPopMatrix();
}
// Shape class.
class Shape
{
public:
	Shape(float xVal, float yVal, int brush)
	{
		x = xVal; y = yVal; b = brush;
	}
	Shape() {};
	void draw(void); // Function to draw a shape.
	float x, y; // x and y co-ordinates of shape.
	int b; // an int for mapping the shape to a brush
};

// Function to draw a shape.
void Shape::draw()
{

	switch (b)
	{
	case 3:
		glBegin(GL_POLYGON);
		glVertex3f(x, y, -50.0);
		glVertex3f(x+40, y, -50.0);
		glVertex3f(x+40, y+40, -50.0);
		glVertex3f(x, y+40, -50.0);
		glEnd();
		break;
	case 2:
		glBegin(GL_TRIANGLES);
		glVertex3f(x, y, -50.0);
		glVertex3f(x+40, y, -50.0);
		glVertex3f(x+40, y+40, -50.0);
		glEnd();
		break;
	case 1:
		glPushMatrix();
		glTranslatef(x, y, -50.0);
		glutWireSphere(20, 10, 10);
		glPopMatrix();
		break;
	case 0:
		glPushMatrix();
		glTranslatef(x, y, -50.0);
		glutWireCube(40);
		glPopMatrix();
		break;
	}


}

// Vector of shapes.
std::vector<Shape> shapes;


// Function to draw all shapes in the shapes array.
void drawShapes(void)
{
	// Loop through the shapes array drawing each shape.
	for (auto shape : shapes) { shape.draw(); 
	}
}
// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glColor3f(0.0, 0.0, 0.0);
	// Draw cursor
	glPointSize(5.0); // Set point size.
	glBegin(GL_POINTS);
	glVertex3f(Xvalue, Yvalue, -50.0);
	glEnd();

	// Draw shapes that have been selected
	drawShapes();
	// Draw current brush name
	drawName(current_brush_index);
	glutSwapBuffers();
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
	glFrustum(-50.0, 50.0, -50.0, 50.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}


// function that updates brush index
void setBrushIndex(void)
{
	current_brush_index = ++current_brush_index % 4;
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		setBrushIndex();
		glutPostRedisplay();
		break;
	case ' ':
		shapes.push_back(Shape(Xvalue, Yvalue, current_brush_index));
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	case 'w':
		if (key == GLUT_KEY_UP) Yvalue += 5;
		break;
	case 's':
		if (key == GLUT_KEY_DOWN) Yvalue -= 5;
		break;
	case 'a':
		if (key == GLUT_KEY_LEFT) Xvalue -= 5;
		break;
	case 'd':
		if (key == GLUT_KEY_RIGHT) Xvalue += 5;
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) Yvalue += 5;
	if (key == GLUT_KEY_DOWN) Yvalue -= 5;
	if (key == GLUT_KEY_LEFT) Xvalue -= 5;
	if (key == GLUT_KEY_RIGHT) Xvalue += 5;
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the arrow keys or wasd to move the cursor." << std::endl
		<< "Press + to change the brush." << std::endl
		<< "Press space to draw an instance of the brush." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Goodwyn Assignment 3");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	// Register the callback function for non-ASCII key entry.
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
