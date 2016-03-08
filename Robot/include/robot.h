
#ifndef ROBOT_H
#define ROBOT_H

#include <GL/glut.h>
#include <GL/glui.h>

extern GLsizei winWidth;
extern GLsizei winHeight;

extern int main_window;
extern GLUI *glui;

void display();
void winReshapeFcn(GLint w, GLint h);
void specialFunc();
void gluiCode();
void dimensions();
void angles();

#endif

