
#include "global.h"

GLsizei winWidth = 700, winHeight = 700;

void resizeFunk (int newWidth, int newHeight)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, (GLdouble) newWidth, 0.0, (GLdouble) newHeight);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

int main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition (0, 0);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Nick Barnes - Assignment 2");

	glPointSize (5.0);
	glutDisplayFunc (displayFunk);
	menu ();
	glutMouseFunc (mouseFunk);
	glutMotionFunc (motionFunk);
	glutIdleFunc (idleFunk);
	glutKeyboardFunc (bgFunk);
	glutReshapeFunc (resizeFunk);

	glutMainLoop ();
	return 0;
}
