///////////////////////////////////////////////////////////////////////////////////////          
// hemisphere.cpp
//
// This program approximates a hemisphere with an array of latitudinal triangle strips.
//
// Interaction:
// Press P/p to increase/decrease the number of longitudinal slices.
// Press Q/q to increase/decrease the number of latitudinal slices.
// Press x, X, y, Y, z, Z to turn the hemisphere.
//
// Sumanta Guha.
/////////////////////////////////////////////////////////////////////////////////////// 

#define _USE_MATH_DEFINES 

#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static float R = 5.0; // Radius of hemisphere.
static int p = 6; // Number of longitudinal slices.
static int q = 4; // Number of latitudinal slices.
static float turns = 5;
static int n = 10;  // Number of vertix for helix.
static int pitch = 5;
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate hemisphere.
static float offset = -10;
static float spinSpeed = 5;
static float prev_time = 0;
int userinput=0;
// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Drawing routine.
void drawScene(void)
{
	int  i, j;

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	// Command to push the hemisphere, which is drawn centered at the origin, 
	// into the viewing frustum.
	glTranslatef(0.0, 0.0, offset);

	// Commands to turn the hemisphere.
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);

	switch (userinput) {
	case 1:

		// Hemisphere properties.
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0.0, 0.0, 0.0);

		// Array of latitudinal triangle strips, each parallel to the equator, stacked one
		// above the other from the equator to the north pole.
		for (j = 0; j < q; j++)
		{
			// One latitudinal triangle strip.
			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0; i <= p; i++)
			{
				glVertex3f(R * cos((float)(j + 1) / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
					R * sin((float)(j + 1) / q * M_PI / 2.0),
					-R * cos((float)(j + 1) / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
				glVertex3f(R * cos((float)j / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
					R * sin((float)j / q * M_PI / 2.0),
					-R * cos((float)j / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
			}
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0; i <= p; i++)
			{
				glVertex3f(R * cos((float)(j + 1) / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
					-R * sin((float)(j + 1) / q * M_PI / 2.0),
					-R * cos((float)(j + 1) / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
				glVertex3f(R * cos((float)j / q * M_PI / 2.0) * cos(2.0 * (float)i / p * M_PI),
					-R * sin((float)j / q * M_PI / 2.0),
					-R * cos((float)j / q * M_PI / 2.0) * sin(2.0 * (float)i / p * M_PI));
			}
			glEnd();
		}
		break;

	case 2:
		// Helix properties.
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
		// calculate number of turns based on height and radius of helix
	    //turns = pitch / (2 * M_PI * R);
		// calculate number of vertices based on number of turns
		int numVertices = (int)(turns * n);

		// draw the helix
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= numVertices; i++) {
			float angle = i * 2 * M_PI / n;
			float x = R * cos(angle);
			float y = R * sin(angle);
			float z = i * pitch / numVertices;
			//glColor3f(c1, c2,0);
            glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
			glVertex3f(x, y, z);
		}

		glEnd();
	
		break;	
	}
	glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void spinDisplay() {
	Yangle += spinSpeed * (glutGet(GLUT_ELAPSED_TIME) - prev_time) / 1000;
	prev_time = glutGet(GLUT_ELAPSED_TIME); // to indicate refresh rate
	if (Yangle > 360.0) Yangle -= 360.0;
	glutPostRedisplay();
}
void spinDisplayReverse() {

	Yangle -= spinSpeed * (glutGet(GLUT_ELAPSED_TIME) - prev_time) / 1000;
	prev_time = glutGet(GLUT_ELAPSED_TIME); // to indicate refresh rate
	std::cout << Yangle << std::endl;
	if (Yangle > 360.0) Yangle -= 360.0;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplayReverse);

		break;

	default:
		break;
	}
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'P':
		p += 1;
		glutPostRedisplay();
		break;
	case 'p':
		if (p > 3) p -= 1;
		glutPostRedisplay();
		break;
	case 'Q':
		q += 1;
		glutPostRedisplay();
		break;
	case 'q':
		if (q > 3) q -= 1;
		glutPostRedisplay();
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	case 'O':
		offset += 1;
		glutPostRedisplay();
		break;
	case 'o':
		offset -= 1;
		glutPostRedisplay();
		break;
	case ' ':
		glutIdleFunc(NULL);
		break;
	case 'r':
		if (R > 1) {
			R -= 1;
			glutPostRedisplay();
		}
		break;
	case 'R':
		R += 1;
		glutPostRedisplay();
		break;
	case 'h':
		if (pitch > 1) {
			pitch -= 1;
			glutPostRedisplay();
		}
		break;
	case 'H':
		pitch += 1;
		glutPostRedisplay();
		break;
	case 'n':
		if (n > 5) {
			n -= 1;
			glutPostRedisplay();
		}
		break;
	case 'N':
		n += 1;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:\n" << std::endl;
	std::cout << "First: choose the shape do you want to draw\n" << std::endl;
	std::cout << "For hemisphere:" << std::endl;
	std::cout << "Press P/p to increase/decrease the number of longitudinal slices." << std::endl
		<< "Press Q/q to increase/decrease the number of latitudinal slices." << std::endl
		<< "Press x, X, y, Y, z, Z to turn the hemisphere.\n" << std::endl;

	std::cout << "For helix:" << std::endl;
	std::cout << "Press N/n to increase/decrease number of vertices used to draw the helix" << std::endl
		<< "Press H/h to increase/decrease pitch of helix." << std::endl
		<< "Press R/r to increase/decrease radius of the helix.\n" << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	std::cout << "Which shape do you want to draw:\n1) sphere\n2) helix\n>> ";
	std::cin >> userinput;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hemisphere.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouse);
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
