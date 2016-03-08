
#include "perspective.h"
#include "robot.h"
#include <iostream>
using namespace std;

Point start, end;
GLint button = GLUT_LEFT_BUTTON, action = GLUT_UP;

GLfloat xPan = 0, yPan = 0;
GLint persHoriz = 0, persVert = 0;
GLint nearPlane = 40;

void viewRobot()
{
	gluLookAt (200, -persHoriz, -persVert, 0, 0, 0, 0, 0, 1);
	glTranslatef (yPan, xPan, 0);
}

void mouseFunc(GLint click, GLint state, GLint xPos, GLint yPos)
{
	action = state;
	button = click;
	if (state == GLUT_DOWN)
		start  = Point(xPos, winHeight - yPos);
}

void motionFunc(GLint xPos, GLint yPos)
{
	if (action == GLUT_DOWN) {
		end = Point(xPos, winHeight - yPos);
		if (button == GLUT_LEFT_BUTTON) {
			xPan = end.x - start.x; 
			yPan = end.y - start.y; 
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			persHoriz = end.x - start.x;
			persVert = end.y - start.y;
		}
	}
	glutPostRedisplay();
}

void keyFunc(GLubyte key, GLint xPos, GLint yPos)
{
	switch (key) {
	case 'o':
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho (-winWidth/2, winWidth/2,
				 -winHeight/2, winHeight/2,
				 -1000, 1000);
		glutPostRedisplay();
		break;

	case 'p':
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum (-75, 75,	-75, 75, nearPlane, 1000);
		glutPostRedisplay();
		break;
	}
}

void specialFunc(int key, int xPos, int yPos)
{
	if (key == GLUT_KEY_UP)
		nearPlane += 1;
	else if (key == GLUT_KEY_DOWN)
		nearPlane -= 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum (-75, 75,	-75, 75, nearPlane, 1000);
	glutPostRedisplay();
}
