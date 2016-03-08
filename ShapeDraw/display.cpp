
#include "global.h"

GLint lumen = 0, speed = 0;
GLboolean readyDraw = false;
GLint dir = +1.0;

void displayFunk (void)
{
	background();
	glClear (GL_COLOR_BUFFER_BIT);

	if (readyDraw) {
		
		switch (color) {
		case RED:   glColor3f (1.0, 0.0, 0.0); break;
		case GREEN: glColor3f (0.0, 1.0, 0.0); break;
		case BLUE:  glColor3f (0.0, 0.0, 1.0); break;
		}

		switch (shape) {
		case TRI:  drawTri();  break;
		case RECT: drawRect(); break;
		case CIRC: drawCirc(); break;
		case POLY: drawPoly(); break;
		}

		if (!newShape && (action == GLUT_DOWN))
			switch (spin) {
				case WIN: rotateWin ();	break;
				case OBJ: rotateObj ();	break;
			}
	}

	glFlush ();
	glutSwapBuffers ();
}

void background () {
	switch (bg) {
		case CYAN:    
			if (lumen <= 0)
				glClearColor (0.0, 1.0 + lumen/100.0, 1.0 + lumen/100.0, 0.0);
			else if (lumen > 0)
				glClearColor (lumen/100.0, 1.0, 1.0, 0.0);
			break;
		case MAGENTA: 
			if (lumen <= 0)
				glClearColor (1.0 + lumen/100.0, 0.0, 1.0 + lumen/100.0, 0.0);
			else if (lumen > 0)
				glClearColor (1.0, lumen/100.0, 1.0, 0.0);
			break;
		case YELLOW:
			if (lumen <= 0)
				glClearColor (1.0 + lumen/100.0, 1.0 + lumen/100.0, 0.0, 0.0);
			else if (lumen > 0)
				glClearColor (1.0, 1.0, lumen/100.0, 0.0);
			break;
		case WHITE:
			if (lumen <= 0)
				glClearColor (1.0 + lumen/100.0, 1.0 + lumen/100.0, 1.0 + lumen/100.0, 0.0);
			else if (lumen > 0)
				glClearColor (1.0, 1.0, 1.0, 0.0);
			break;
	}
}

//Each drawing function has its own interperetation
//	of elements in vectror<Point> pointAry
void drawTri ()
{
	switch (style) {
		case VERTEX:
			glBegin (GL_POINTS);
				triAlg();
			glEnd (); break;

		case EDGE:
			glBegin (GL_LINE_LOOP);
				triAlg();
			glEnd (); break;

		case FILL:
			glBegin (GL_POLYGON);
				triAlg();
			glEnd (); break;
	}
}

void triAlg() {
	GLfloat x1 = pointAry[0].x,	y1 = pointAry[0].y,
			x2 = pointAry[1].x, y2 = pointAry[1].y;

	glVertex2f (x2, y2);
	glVertex2f (triCalc(x1, x2, y1, y2), triCalc(y1, y2, x2, x1));
	glVertex2f (triCalc(x1, x2, y2, y1), triCalc(y1, y2, x1, x2));
}

//Nifty math trick I came up with
GLfloat triCalc (GLfloat a, GLfloat b, GLfloat c, GLfloat d) {
	return 0.5*( 3*a - b + sqrt(3.0)*(c - d) );
}

void drawRect ()
{
	switch (style) {
		case VERTEX:
			glBegin (GL_POINTS);
				rectAlg();
			glEnd (); break;

		case EDGE:
			glBegin (GL_LINE_LOOP);
				rectAlg();
			glEnd (); break;

		case FILL:
			glBegin (GL_POLYGON);
				rectAlg();
			glEnd (); break;
	}
}

void rectAlg() {
	glVertex2f (pointAry[0].x, pointAry[0].y);
	glVertex2f (pointAry[1].x, pointAry[0].y);
	glVertex2f (pointAry[1].x, pointAry[1].y);
	glVertex2f (pointAry[0].x, pointAry[1].y);
}

void drawCirc ()
{
	switch (style) {
		case VERTEX:
			glBegin (GL_POINTS);
				glVertex2i (pointAry[0].x, pointAry[0].y);
			glEnd (); break;

		case EDGE:
			glBegin (GL_LINE_LOOP);
				circAlg();
			glEnd (); break;
			
		case FILL:
			glBegin (GL_POLYGON);
				circAlg();
			glEnd (); break;
	}
}

void circAlg () {
	GLfloat dtheta = 0.1;
	GLfloat radius = dist (pointAry[0], pointAry[1]);
	for (GLfloat theta = 0.0; theta < 2*PI; theta += dtheta)
		glVertex2f (pointAry[0].x + radius*cos(theta),
				pointAry[0].y + radius*sin(theta) );
}

//Distance formula
GLfloat dist (Point pt1, Point pt2) {
	return sqrt ( pow (GLfloat (pt2.x-pt1.x), 2) + pow (GLfloat (pt2.y-pt1.y), 2) );
}

void drawPoly ()
{
	switch (style) {
		case VERTEX:
			glBegin (GL_POINTS);
				polyAlg();
			glEnd (); break;
	
		case EDGE:
			glBegin (GL_LINE_LOOP);
				polyAlg();
			glEnd (); break;

		case FILL: 
			glBegin (GL_TRIANGLE_STRIP);
				polyAlg();
			glEnd (); break;
	}
}

void polyAlg () {
	for (GLint idx = 0; idx < (GLint)pointAry.size(); idx++)
		glVertex2f (pointAry[idx].x, pointAry[idx].y);
}

void rotateWin () {
	glTranslatef (winWidth/2, winHeight/2, 0.0);
	glRotatef (dir*5.0*(1+speed/50.0), 0.0, 0.0, 1.0);
	glTranslatef (-winWidth/2, -winHeight/2, 0.0);
}

void rotateObj () {
	glTranslatef (pointAry[0].x, pointAry[0].y, 0.0);
	glRotatef (dir*5.0*(1+speed/50.0), 0.0, 0.0, 1.0);
	glTranslatef (-pointAry[0].x, -pointAry[0].y, 0.0);
}
