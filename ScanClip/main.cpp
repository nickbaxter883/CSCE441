
#include "global.h"
#include "clip.h"
#include "scan.h"
#include <iostream>

/******************************************************************
	Notes:
	Image size is 400 by 400 by default.  You may adjust this if
		you want to.
	You can assume the window will NOT be resized.
	Call clearFramebuffer to clear the entire framebuffer.
	Call setFramebuffer to set a pixel.  This should be the only
		routine you use to set the color (other than clearing the
		entire framebuffer).  drawit() will cause the current
		framebuffer to be displayed.
	As is, your scan conversion should probably be called from
		within the display function.  There is a very short sample
		of code there now.
	You may add code to any of the subroutines here,  You probably
		want to leave the drawit, clearFramebuffer, and
		setFramebuffer commands alone, though.
  *****************************************************************/

Frame screen;
Color palette [12] = {	Color(1.0, 0.0, 0.0), Color(0.0, 1.0, 0.0), Color(0.0, 0.0, 1.0),
						Color(1.0, 1.0, 0.0), Color(0.0, 1.0, 1.0), Color(1.0, 0.0, 1.0),
						Color(0.5, 0.5, 0.0), Color(0.0, 0.5, 0.5), Color(1.0, 1.0, 1.0),
						Color(0.0, 0.5, 0.0), Color(1.0, 0.5, 0.5), Color(0.5, 0.5, 1.0) };

void displayGl()
{
	glClear (GL_COLOR_BUFFER_BIT);
	cout << "Draw func" << endl;
	for (unsigned int idx = 0; idx < shapes.size(); idx++) {

		Clipper chopper(shapes[idx], clip_min, clip_max);
		shapes[idx] = chopper.clip();

		cout << "poly " << idx << ": ";
		shapes[idx].print();

		shapes[idx].draw();
	}
	
	glFlush();
}

void display()
{
	cout << "Draw func" << endl;
	for (unsigned int idx = 0; idx < shapes.size(); idx++) {

		Clipper chopper(shapes[idx], clip_min, clip_max);
		shapes[idx] = chopper.clip();

		cout << "poly " << idx << ": ";
		shapes[idx].print();

		screen.shade = palette[idx%12];
		Scanner render(shapes[idx]);
		render.scan();

		screen.drawit();
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, ImageW, 0.0, ImageH);
	screen.clearFramebuffer();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ImageW,ImageH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Nick Barnes - Homework 3");

	init();	
	glutDisplayFunc(display);
	input();
	glutMainLoop();

	return 0;
}

