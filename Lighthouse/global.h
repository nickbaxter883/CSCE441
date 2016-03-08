
#ifndef GLOBAL_H
#define GLOBAL_H
#include <GL/glut.h>
#include "point.h"

GLsizei winWidth = 600;
GLsizei winHeight = 600;
GLint main_window;

Point eye(20, 0, 20);
Point view(-1, 0, -1);
Point up(0, 0, 1);
Point side;
GLfloat xrot = 0, yrot = 0;
GLint speed = 0, animation = 0, iterations = 2880;
const GLfloat PI = 3.141592654;

#endif

