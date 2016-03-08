
#include "model.h"

GLint BodyH = 200;
GLint BodyR = 15;

GLint HeadR = 50;
GLint HeadAngle = 0;

GLint ArmL = 100;
GLint ArmR = 10;
GLint ArmVertAngle = 45;
GLint ArmLatAngle = 30;

GLint ClawL = 50;
GLint ClawR = 5;
GLint ClawVertAngle = 45;
GLint ClawRotAngle = 0;

GLint FingerL = 30;
GLint FingerR = 7;
GLint FingerAngle = 45;

GLint LegL = 100;
GLint LegR = 10;
GLint LegVertAngle = 60;
GLint LegRotAngle = 45;

GLint FootL = 100;
GLint FootR = 10;
GLint FootAngle = 90;

void drawRobot()
{
	glPushMatrix();
		glTranslatef (0, 0, -BodyH/2);
		drawBody();
	glPopMatrix();

	//Head
	glPushMatrix();
		glTranslatef (0, 0, BodyH/2);
		glRotatef (HeadAngle, 0.0, 0.0, 1.0);
		drawHead();
	glPopMatrix();

	//Arms
	glPushMatrix();
		glRotatef (ArmVertAngle, 1.0, 0.0, 0.0);
		glRotatef (ArmLatAngle, 0.0, 1.0, 0.0);
		drawArm();
	glPopMatrix();

	glPushMatrix();
		glRotatef (-ArmVertAngle, 1.0, 0.0, 0.0);
		glRotatef (ArmLatAngle, 0.0, 1.0, 0.0);
		drawArm();
	glPopMatrix();

	//Legs
	glPushMatrix();
		glTranslatef (0, 0, -BodyH/2);
		glRotatef (LegRotAngle, 0.0, 0.0, 1.0);
		glRotatef (-LegVertAngle, 1.0, 0.0, 0.0);
		drawLeg();
	glPopMatrix();

	glPushMatrix();
		glTranslatef (0, 0, -BodyH/2);
		glRotatef (LegRotAngle+90, 0.0, 0.0, 1.0);
		glRotatef (-LegVertAngle, 1.0, 0.0, 0.0);
		drawLeg();
	glPopMatrix();

	glPushMatrix();
		glTranslatef (0, 0, -BodyH/2);
		glRotatef (LegRotAngle+180, 0.0, 0.0, 1.0);
		glRotatef (-LegVertAngle, 1.0, 0.0, 0.0);
		drawLeg();
	glPopMatrix();

	glPushMatrix();
		glTranslatef (0, 0, -BodyH/2);
		glRotatef (LegRotAngle+270, 0.0, 0.0, 1.0);
		glRotatef (-LegVertAngle, 1.0, 0.0, 0.0);
		drawLeg();
	glPopMatrix();
}

void drawBody() {
	glColor3f (1.0, 0.0, 0.0);
	GLUquadricObj *body = gluNewQuadric();
	gluQuadricDrawStyle (body, GLU_FILL);
	gluCylinder (body, BodyR, BodyR, BodyH, 6, 4);
}

void drawHead() {
	glColor3f (1.0, 1.0, 0.0);
	glScalef (HeadR, HeadR, HeadR);
	glutSolidIcosahedron();
	glColor3f (0.0, 0.0, 0.0);
	glScalef (1.01, 1.01, 1.01);
	glutWireIcosahedron();
}

void drawArm() {
	glColor3f (0.0, 0.0, 1.0);
	GLUquadricObj *arm = gluNewQuadric();
	gluQuadricDrawStyle (arm, GLU_FILL);
	gluCylinder (arm, ArmR, ArmR, ArmL, 6, 4);

	glPushMatrix();
		glTranslatef(0.0, 0.0, ArmL);
		glRotatef(ClawRotAngle, 0.0, 0.0, 1.0);
		glRotatef(ClawVertAngle, 0.0, 1.0, 0.0);
		drawClaw();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.0, ArmL);
		glRotatef(ClawRotAngle+90, 0.0, 0.0, 1.0);
		glRotatef(ClawVertAngle, 0.0, 1.0, 0.0);
		drawClaw();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.0, ArmL);
		glRotatef(ClawRotAngle+180, 0.0, 0.0, 1.0);
		glRotatef(ClawVertAngle, 0.0, 1.0, 0.0);
		drawClaw();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.0, ArmL);
		glRotatef(ClawRotAngle+270, 0.0, 0.0, 1.0);
		glRotatef(ClawVertAngle, 0.0, 1.0, 0.0);
		drawClaw();
	glPopMatrix();
}

void drawClaw() {
	glColor3f (0.0, 1.0, 0.0);
	GLUquadricObj *claw = gluNewQuadric();
	gluQuadricDrawStyle (claw, GLU_FILL);
	gluCylinder (claw, ClawR, ClawR, ClawL, 6, 4);

	glPushMatrix();
		glTranslatef(0.0, 0.0, ClawL);
		glRotatef(-FingerAngle, 0.0, 1.0, 0.0);
		drawFinger();
	glPopMatrix();
}

void drawFinger() {
	glColor3f(1.0, 0.5, 0.5);
	GLUquadricObj *finger = gluNewQuadric();
	gluQuadricDrawStyle (finger, GLU_FILL);
	gluCylinder (finger, FingerR, 0.0, FingerL, 6, 4);
}

void drawLeg() {
	glColor3f (0.0, 1.0, 0.0);
	GLUquadricObj *leg = gluNewQuadric();
	gluQuadricDrawStyle (leg, GLU_FILL);
	gluCylinder (leg, LegR, LegR, LegL, 6, 4);

	glPushMatrix();
		glTranslatef(0.0, 0.0, LegL);
		glRotatef(-FootAngle, 1.0, 0.0, 0.0);
		drawFoot();
	glPopMatrix();
}

void drawFoot() {
	glColor3f(1.0, 0.0, 1.0);
	GLUquadricObj *foot = gluNewQuadric();
	gluQuadricDrawStyle (foot, GLU_FILL);
	gluCylinder (foot, FootR, 0.0, FootL, 6, 4);
}

