
#include "robot.h"
#include "model.h"
#include "perspective.h"

GLsizei winWidth = 600;
GLsizei winHeight = 600;
GLUI *glui;
GLint main_window;

void display()
{
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	viewRobot();
	drawRobot();

	glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200,50);
	glutInitWindowSize(winWidth,winHeight);

	main_window = glutCreateWindow("Nick Barnes - Homework 4");
	glViewport(0, 0, winWidth, winHeight);
	glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutKeyboardFunc(keyFunc);
	glutSpecialFunc(specialFunc);
	
	glEnable(GL_DEPTH_TEST);
	gluiCode();

	keyFunc('o', 0, 0);
	glutMainLoop();
}

void gluiCode()
{
	glui = GLUI_Master.create_glui("Interface", 0, winWidth+200, 100);
	glui->set_main_gfx_window (main_window);

	dimensions();
	angles();
}

void dimensions()
{
	GLUI_Rollout *dim = glui->add_rollout(
		"Dimensions", false);

	GLUI_Spinner *headSpinner = glui->add_spinner_to_panel(
		dim, "Head Radius: ", GLUI_SPINNER_INT, &HeadR);

	glui->add_separator_to_panel(dim);

	GLUI_Spinner *bodyHSpinner = glui->add_spinner_to_panel(
		dim, "Body Height: ", GLUI_SPINNER_INT, &BodyH);
	GLUI_Spinner *bodyRSpinner = glui->add_spinner_to_panel(
		dim, "Body Radius: ", GLUI_SPINNER_INT, &BodyR);

	glui->add_separator_to_panel(dim);

	GLUI_Spinner *armLSpinner = glui->add_spinner_to_panel(
		dim, "Arm Length: ", GLUI_SPINNER_INT, &ArmL);
	GLUI_Spinner *armRSpinner = glui->add_spinner_to_panel(
		dim, "Arm Radius: ", GLUI_SPINNER_INT, &ArmR);

	glui->add_separator_to_panel(dim);

	GLUI_Spinner *clawLSpinner = glui->add_spinner_to_panel(
		dim, "Claw Length: ", GLUI_SPINNER_INT, &ClawL);
	GLUI_Spinner *clawRSpinner = glui->add_spinner_to_panel(
		dim, "Claw Radius: ", GLUI_SPINNER_INT, &ClawR);

	glui->add_separator_to_panel(dim);

	GLUI_Spinner *legLSpinner = glui->add_spinner_to_panel(
		dim, "Leg Length: ", GLUI_SPINNER_INT, &LegL);
	GLUI_Spinner *legRSpinner = glui->add_spinner_to_panel(
		dim, "Leg Radius: ", GLUI_SPINNER_INT, &LegR);

	glui->add_separator_to_panel(dim);

	GLUI_Spinner *footLSpinner = glui->add_spinner_to_panel(
		dim, "Foot Length: ", GLUI_SPINNER_INT, &FootL);
	GLUI_Spinner *footRSpinner = glui->add_spinner_to_panel(
		dim, "Foot Radius: ", GLUI_SPINNER_INT, &FootR);

	glui->add_separator_to_panel(dim);

	GLUI_Spinner *fingerLSpinner = glui->add_spinner_to_panel(
		dim, "Finger Length: ", GLUI_SPINNER_INT, &FingerL);
	GLUI_Spinner *fingerRSpinner = glui->add_spinner_to_panel(
		dim, "Finger Radius: ", GLUI_SPINNER_INT, &FingerR);

	headSpinner->set_int_limits(20, 100);
	bodyHSpinner->set_int_limits(100, 400);
	bodyRSpinner->set_int_limits(10, 30);
	armLSpinner->set_int_limits(20, 200);
	armRSpinner->set_int_limits(5, 15);
	clawLSpinner->set_int_limits(25, 75);
	clawRSpinner->set_int_limits(5, 10);
	legLSpinner->set_int_limits(50, 200);
	legRSpinner->set_int_limits(5, 15);
	footLSpinner->set_int_limits(50, 150);
	footRSpinner->set_int_limits(10, 20);
	fingerLSpinner->set_int_limits(15, 50);
	fingerRSpinner->set_int_limits(5, 10);
}

void angles()
{
	GLUI_Rollout *angle = glui->add_rollout(
		"Angles", true);

	GLUI_Spinner *headSpinner = glui->add_spinner_to_panel(
		angle, "Head Angle: ", GLUI_SPINNER_INT, &HeadAngle);

	glui->add_separator_to_panel(angle);

	GLUI_Spinner *vertArmSpinner = glui->add_spinner_to_panel(
		angle, "Vertical Arm Angle: ", GLUI_SPINNER_INT, &ArmVertAngle);
	GLUI_Spinner *latArmSpinner = glui->add_spinner_to_panel(
		angle, "Lateral Arm Angle: ", GLUI_SPINNER_INT, &ArmLatAngle);

	glui->add_separator_to_panel(angle);

	GLUI_Spinner *vertClawSpinner = glui->add_spinner_to_panel(
		angle, "Grip Angle: ", GLUI_SPINNER_INT, &ClawVertAngle);
	GLUI_Spinner *rotClawSpinner = glui->add_spinner_to_panel(
		angle, "Drill Angle: ", GLUI_SPINNER_INT, &ClawRotAngle);

	glui->add_separator_to_panel(angle);

	GLUI_Spinner *legVertSpinner = glui->add_spinner_to_panel(
		angle, "Squat Angle: ", GLUI_SPINNER_INT, &LegVertAngle);
	GLUI_Spinner *legRotSpinner = glui->add_spinner_to_panel(
		angle, "Pelvic Angle: ", GLUI_SPINNER_INT, &LegRotAngle);

	glui->add_separator_to_panel(angle);

	GLUI_Spinner *footSpinner = glui->add_spinner_to_panel(
		angle, "Foot Angle: ", GLUI_SPINNER_INT, &FootAngle);
	GLUI_Spinner *fingerSpinner = glui->add_spinner_to_panel(
		angle, "Finger Angle: ", GLUI_SPINNER_INT, &FingerAngle);

	headSpinner->set_int_limits(-180, 180);
	vertArmSpinner->set_int_limits(0, 180);
	latArmSpinner->set_int_limits(0, 90);
	vertClawSpinner->set_int_limits(0, 90);
	rotClawSpinner->set_int_limits(-180, 180);
	legVertSpinner->set_int_limits(45, 135);
	legRotSpinner->set_int_limits(-180, 180);
	footSpinner->set_int_limits(45, 135);
	fingerSpinner->set_int_limits(0, 90);
}

