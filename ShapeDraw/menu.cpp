
#include "global.h"

Color color = RED;
Shape shape = TRI;
Spin spin = WIN;

void menu (void)
{
	GLint subShape, subColor, subRot;

	subShape = glutCreateMenu (shapeMenu);
		glutAddMenuEntry ("Triangle", 1);
		glutAddMenuEntry ("Rectangle", 2);
		glutAddMenuEntry ("Circle", 3);
		glutAddMenuEntry ("Polygon", 4);

	subColor = glutCreateMenu (colorMenu);
		glutAddMenuEntry ("Red", 1);
		glutAddMenuEntry ("Green", 2);
		glutAddMenuEntry ("Blue", 3);

	subRot = glutCreateMenu (rotationMenu);
		glutAddMenuEntry ("Window", 1);
		glutAddMenuEntry ("Object", 2);

	glutCreateMenu (mainMenu);
		glutAddSubMenu ("Shape", subShape);
		glutAddSubMenu ("Color", subColor);
		glutAddSubMenu ("Rotation", subRot);

	glutAttachMenu (GLUT_MIDDLE_BUTTON);
}

void mainMenu (GLint select) {}

void shapeMenu (GLint select)
{
	switch (select) {
		case 1: shape = TRI;  break;
		case 2: shape = RECT; break;
		case 3: shape = CIRC; break;
		case 4: shape = POLY; break;
	}
	reset();
}

void colorMenu (GLint select)
{
	switch (select) {
		case 1: color = RED ;  break;
		case 2: color = GREEN; break;
		case 3: color = BLUE;  break;
	}
	glutPostRedisplay ();
}

void rotationMenu (GLint select)
{
	switch (select) {
		case 1: spin = WIN; break;
		case 2: spin = OBJ; break;
	}
}

void reset () {
	newShape = true;
	currentPoint = 0;
	readyDraw = false;
	pointAry.clear();
	glutPostRedisplay ();
}
