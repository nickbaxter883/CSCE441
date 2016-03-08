
#ifndef GLOBAL_H_
#define GLOBAL_H_

//includes:
#include <cstdlib>
#include "glut.h"
#include <GL/gl.h>
#include <vector>
#include <cmath>
using namespace std;

//Global vars:

//Window
extern GLsizei winWidth, winHeight;

//Display control
const GLfloat PI = 3.141592654;
extern GLint lumen, speed;
extern GLboolean readyDraw;
extern GLint currentPoint;
extern GLint dir;

//Mouse control
class Point {
public:
	GLfloat x, y;

	Point () { x=0; y=0; }
	Point (GLfloat xPos, GLint yPos) : x (xPos), y (yPos) { }
	Point (const Point& pt) { x = pt.x; y = pt.y; }

	GLboolean equals (Point& pt) {
		return (this->x == pt.x) && (this->y == pt.x);
	}
};
extern Point home, end;
extern vector<Point> pointAry;
extern GLboolean newShape;
extern GLint button;
extern GLint action;

//Menu codes
enum Color {RED, GREEN, BLUE};
enum Shape {TRI, RECT, CIRC, POLY};
enum Spin {WIN, OBJ};

//Menu control
extern Color color;
extern Shape shape;
extern Spin spin;

//Key codes
enum Bg {CYAN, MAGENTA, YELLOW, WHITE};
enum Style {VERTEX, EDGE, FILL};

//Key controls
extern Style style;
extern Bg bg;

//Prototypes:

//Display funcs
void displayFunk ();
void bgFunk (GLubyte key, GLint xPos, GLint yPos);
void background ();
void drawTri ();
void triAlg ();
void drawRect ();
void rectAlg ();
void drawCirc ();
void circAlg ();
void drawPoly ();
void polyAlg ();
float triCalc (GLfloat a, GLfloat b, GLfloat c, GLfloat d);
float dist (Point pt1, Point pt2);
void rotateWin ();
void rotateObj ();

//Mouse funcs
void mouseFunk (GLint click, GLint action, GLint xPos, GLint yPos);
void motionFunk (GLint xPos, GLint yPos);
void idleFunk ();

//Menu funcs
void menu ();
void mainMenu (GLint select);
void shapeMenu (GLint select);
void colorMenu (GLint select);
void rotationMenu (GLint select);
void reset ();

#endif
