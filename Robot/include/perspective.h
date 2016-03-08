
#ifndef PERSPECTIVE_H 
#define PERSPECTIVE_H

#include <GL/glut.h>
#include <GL/glui.h>

class Point {
public:
	GLint x, y;
	Point () { x=0; y=0; }
	Point (GLint xPos, GLint yPos): x(xPos), y(yPos) {}
	Point (const Point& p) { x = p.x; y = p.y; }
};
enum KeyType {};

extern GLint persHoriz;
extern GLint persVert;
extern GLfloat xp, yp, zp;
extern int nearPlane;

void viewRobot();
void mouseFunc(GLint button, GLint action, GLint xPos, GLint yPos);
void motionFunc(GLint xPos, GLint yPos);

void keyFunc(GLubyte key, GLint xPos, GLint yPos);
void specialFunc(int key, int xPos, int yPos);

#endif

