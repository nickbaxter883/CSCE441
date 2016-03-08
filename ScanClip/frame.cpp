
#include <GL/glut.h>
#include "frame.h"

// Draws the scene
void Frame::drawit(void)
{
   glDrawPixels(ImageW,ImageH,GL_RGB,GL_FLOAT,framebuffer);
   glFlush();
}

// Clears framebuffer to black
void Frame::clearFramebuffer()
{
	int i,j;

	for(i=0;i<ImageH;i++) {
		for (j=0;j<ImageW;j++) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

// Sets pixel x,y to the color RGB
void Frame::setFramebuffer(int x, int y)
{
	if (shade.r<=1.0)
		if (shade.r>=0.0)
			framebuffer[x][y][0]=shade.r;
		else
			framebuffer[x][y][0]=0.0;
	else
		framebuffer[x][y][0]=1.0;
	if (shade.g<=1.0)
		if (shade.g>=0.0)
			framebuffer[x][y][1]=shade.g;
		else
			framebuffer[x][y][1]=0.0;
	else
		framebuffer[x][y][1]=1.0;
	if (shade.b<=1.0)
		if (shade.b>=0.0)
			framebuffer[x][y][2]=shade.b;
		else
			framebuffer[x][y][2]=0.0;
	else
		framebuffer[x][y][2]=1.0;
}

