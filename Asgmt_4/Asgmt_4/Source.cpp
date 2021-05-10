#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 


// Globals.
static float x = 0.0, y = 0.0, z = 0.0;
static float d = 0.0;
static float s = 0.0;
static float sh = 50.0;
// Function for writing text to the screen
void writeBitmapString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Drawing routine.
void drawScene(void)
{
	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 0.0 };
	float lightDif[] = { d, d, d, 1.0 };
	float lightSpec[] = { s, s, s, 1.0 };
	float lightPos[] = { x, y, z, 0.0 };
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };
	
	float matShine[] = { sh };
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
	
	glEnable(GL_LIGHT0); // Enable particular light source.
	//  use a call to gluLookAt to simulate an eye point of (0, 1.0, 3.0) looking toward the -z axis and with an up direction of (0, 1, 0).
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glFrontFace(GL_CW);
	gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glutSolidTeapot(1.0);
	glutSwapBuffers();
}

void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST); // Enable depth testing.

	// Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);

	// Material property vectors.
	float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };
	float matAmbAndDif[] = { 0.9, 0.2, 0.2, 0.0 };

	// Material properties of ball.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	// Cull back faces.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		sh += 5.0;
		glutPostRedisplay();
		break;
	case '-':
		sh -= 5.0;
		glutPostRedisplay();
		break;
	case ',':
		z += 0.5;
		glutPostRedisplay();
		break;
	case '.':
		z -= 0.5;
		glutPostRedisplay();
		break;
	case 's':
		if (s == 0.0){ s = 1.0;}
		else s = 0.0;
		glutPostRedisplay();
		break;
	case 'd':
		if (d == 0.0){ d = 1.0;}
		else d = 0.0;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) y += 0.5;
	if (key == GLUT_KEY_DOWN) y -= 0.5;
	if (key == GLUT_KEY_LEFT) x -= 0.5;
	if (key == GLUT_KEY_RIGHT) x += 0.5;
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the arrow keys to move the ." << std::endl
		<< "Press + to change " << std::endl
		<< "Press ." << std::endl;
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
	glutCreateWindow("Goodwyn Assignment 4");
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
