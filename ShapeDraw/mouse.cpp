
#include "global.h"

GLboolean newShape = true;
GLint currentPoint = 0;
Point home, end;
vector<Point> pointAry;
GLint button = GLUT_LEFT_BUTTON;
GLint action = GLUT_UP;

//button must change to enter this function
void mouseFunk (GLint click, GLint state, GLint xPos, GLint yPos)
{
	Point mouse (xPos, winHeight - yPos);
	button = click;
	action = state;

	//Creating shape
	if (newShape) {
		if (button == GLUT_LEFT_BUTTON) {
			if (action == GLUT_DOWN) {
				//Assign start
				pointAry.push_back (mouse);
			}
			else if (action == GLUT_UP) {
				//Complete shape
				pointAry.push_back (mouse);
				currentPoint++;
				glutPostRedisplay ();
				if (shape != POLY) {
					newShape = false;
				}
			}
		}
		else if (button == GLUT_RIGHT_BUTTON && shape == POLY) {
			//Complete Polygon
			glutPostRedisplay ();
			newShape = false;
		}
	}

	//Rotation and background
	else {
		//Assign home
		if (action == GLUT_DOWN)
			home = Point(mouse);
		else {
			lumen = 0.0;
			speed = 0.0;
			glMatrixMode (GL_MODELVIEW);
			glLoadIdentity ();
			glutPostRedisplay ();
		}
	}
}

//action must be GLUT_DOWN to enter this function
void motionFunk (GLint xPos, GLint yPos)
{
	Point mouse (xPos, winHeight - yPos);

	if (newShape) {
		if (button == GLUT_LEFT_BUTTON) {
			//Sketch outline
			if (!readyDraw) {
				pointAry.push_back (mouse);
				currentPoint++;
			}
			else
				pointAry[currentPoint] = Point(mouse);
			readyDraw = true;
			glutPostRedisplay ();
		}
		//else nothing happens for right or center drag
	}

	//Update animation
	else {
		if (button == GLUT_LEFT_BUTTON)
			spin = WIN;
		else if (button == GLUT_RIGHT_BUTTON)
			spin = OBJ;
		lumen = mouse.x - home.x;
		if (lumen < -100)
			lumen = -100;
		else if (lumen > 100)
			lumen = 100;
		speed = mouse.y - home.y;
		if (speed < -50)
			speed = -50;
		else if (speed > 50)
			speed = 50;
		glutPostRedisplay ();
	}
}

//Animate
void idleFunk (void)
{
	if ((action == GLUT_DOWN) && !newShape) {
		if (button == GLUT_LEFT_BUTTON)
			dir = +1.0;
		else if (button == GLUT_RIGHT_BUTTON)
			dir = -1.0;
		glutPostRedisplay ();
	}
}
