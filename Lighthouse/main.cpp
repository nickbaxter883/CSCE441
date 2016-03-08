
#include "global.h"
#include "input.h"
#include "load.h"
#include "light.h"

void idleFunc() {
	if (speed) {
		eye = eye + speed/50.0*view;
	}
	animation = animation%iterations + 1;
	glutPostRedisplay();
}

GLvoid resizeScene(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(90.0f,(GLfloat)width/(GLfloat)height,1,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200,50);
	glutInitWindowSize(winWidth,winHeight);
	main_window = glutCreateWindow("Nick Barnes - Homework 6");

	glutDisplayFunc(drawScene);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutKeyboardFunc(keyFunc);
	glutIdleFunc(idleFunc);
	glutReshapeFunc(resizeScene);

	setLighting();
	//gluiCode();
	glEnable(GL_TEXTURE_2D);
	LoadGLTextures();
    glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

