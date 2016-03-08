
#ifndef INPUT_H
#define INPUT_H
#include "global.h"

Point start, end;
GLint button = GLUT_LEFT_BUTTON, action = GLUT_UP;

void mouseFunc(GLint click, GLint state, GLint xPos, GLint yPos)
{
    action = state;
    button = click;
    if (state == GLUT_DOWN)
        start  = Point(xPos, winHeight - yPos, 0);
}

void motionFunc(GLint xPos, GLint yPos)
{
    if (action == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
    	end = Point(xPos, winHeight - yPos, 0);
        xrot = end.x - start.x;
        yrot = end.y - start.y;
		//change heading
		side = view.crossProd(up);
		up = side.crossProd(view);
		view = cos(PI/180*yrot)*view + sin(PI/180*yrot)*up;
		view = cos(PI/180*xrot)*view + sin(PI/180*xrot)*side;

		//normalize
		up = up.norm();
		view = view.norm();
		
    	glutPostRedisplay();
		start = end;
    }
}

void keyFunc(GLubyte key, GLint xPos, GLint yPos)
{
	switch (key) {
	case 'w':
		speed++;
		break;
	case 'a':
		side = view.crossProd(up);
		up = cos(PI/90)*up - sin(PI/90)*side;
		break;
	case 'd':
		side = view.crossProd(up);
		up = cos(PI/90)*up + sin(PI/90)*side;
		break;
	case 's':
		speed--;
		break;
	case ' ':
		speed = 0;
	}
	glutPostRedisplay();
}

#endif

