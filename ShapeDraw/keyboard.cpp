
#include "global.h"

Style style = VERTEX;
Bg bg = CYAN;

void bgFunk (GLubyte key, GLint xPos, GLint yPos)
{
	switch (key) {
		case 'c': bg = CYAN;    break;
		case 'm': bg = MAGENTA; break;
		case 'y': bg = YELLOW;  break;
		case 'w': bg = WHITE;   break;

		case '1': style = VERTEX; break;
		case '2': style = EDGE;   break;
		case '3': style = FILL;   break;

		default: return;
	}
	glutPostRedisplay();
}
