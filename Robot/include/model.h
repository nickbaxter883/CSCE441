
#ifndef GLOBAL_H
#define GLOBAL_H

#include <GL/glut.h>
#include <GL/glui.h>

extern GLint left;
extern GLint right;
extern GLint bottom;
extern GLint top; 
extern GLint near;
extern GLint far; 

extern GLint BodyH;
extern GLint BodyR;

extern GLint HeadR;
extern GLint HeadAngle;

extern GLint ArmL;
extern GLint ArmR;
extern GLint ArmVertAngle;
extern GLint ArmLatAngle;

extern GLint ClawL;
extern GLint ClawR;
extern GLint ClawVertAngle;
extern GLint ClawRotAngle;

extern GLint FingerL;
extern GLint FingerR;
extern GLint FingerAngle;

extern GLint LegL;
extern GLint LegR;
extern GLint LegVertAngle;
extern GLint LegRotAngle;

extern GLint FootL;
extern GLint FootR;
extern GLint FootAngle;

//GLUI_UPDATE_CB reset();
void drawRobot();
void drawBody();
void drawHead();
void drawArm();
void drawClaw();
void drawFinger();
void drawLeg();
void drawFoot();

#endif

