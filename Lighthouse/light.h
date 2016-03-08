
#ifndef LIGHT_H
#define LIGHT_H

//Side Light
GLfloat light0_ambient[] = { 0.1, 0.1, 0.1, 1.0f }; 
GLfloat light0_diffuse[] = { 0.7, 0.7, 0.7, 1.0f }; 
GLfloat light0_position[]= { 0.0f, 10.0f, 30.0f, 1.0f };

//Side Light
GLfloat light1_ambient[] = { 0.1, 0.1, 0.1, 1.0f }; 
GLfloat light1_diffuse[] = { 0.7, 0.7, 0.7, 1.0f }; 
GLfloat light1_position[]= { 0.0f, -10.0f, 30.0f, 1.0f };

//Spotlight
GLfloat light2_diffuse[]  = { 0.9, 0.0, 0.0, 1.0f }; 
GLfloat light2_specular[] = { 0.7, 0.7, 0.7, 1.0f }; 
GLfloat light2_position[] = { 10.0f, 0.0f, 10.0f, 1.0f };
GLfloat light2_direction[]= { -1, 3*cos(PI/30*animation), -1.0f, 1.0f };

void setLighting() {

	glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse); 
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position); 
	glLightf (GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.5); 
	glLightf (GL_LIGHT3, GL_LINEAR_ATTENUATION, 1.7); 
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse); 
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position); 
	glLightf (GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.5); 
	glLightf (GL_LIGHT3, GL_LINEAR_ATTENUATION, 1.7); 
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_DIFFUSE,  light2_diffuse); 
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position); 
	glLightf (GL_LIGHT2, GL_SPOT_CUTOFF, 15.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction); 
	glLightf (GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
	glEnable (GL_LIGHT2);

	glEnable(GL_LIGHTING);

	/*GLfloat atmoColor [] = {0.8, 0.8, 1.0, 1.0};
	glFogi (GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, atmoColor);
	glFogf(GL_FOG_DENSITY, 0.02f);
	glEnable(GL_FOG);*/
}

#endif

