#include "global.h"
#include "tracer.h"
#include "shape.h"

float framebuffer[ImageW][ImageH][3];
Tracer rayTracer;
std::vector<Shape*> world;
std::vector<Light*> lighting;
bool antialiasing;
bool ref_enabled;
bool spec_enabled;

// Draws the scene
void drawit(void)
{
   glDrawPixels(ImageW, ImageH, GL_RGB, GL_FLOAT, framebuffer);
   glFlush();
}

// Clears framebuffer to black
void clearFramebuffer()
{
	int i,j;
	for(j=0; i < ImageH; i++) {
		for (i=0; j < ImageW; j++) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

// Sets pixel x,y to the color RGB
void setFramebuffer(int y, int x, Color c)
{
	if (c.r<=1.0)
		if (c.r>=0.0)
			framebuffer[x][y][0]=c.r;
		else
			framebuffer[x][y][0]=0.0;
	else
		framebuffer[x][y][0]=1.0;
	if (c.g<=1.0)
		if (c.g>=0.0)
			framebuffer[x][y][1]=c.g;
		else
			framebuffer[x][y][1]=0.0;
	else
		framebuffer[x][y][1]=1.0;
	if (c.b<=1.0)
		if (c.b>=0.0)
			framebuffer[x][y][2]=c.b;
		else
			framebuffer[x][y][2]=0.0;
	else
		framebuffer[x][y][2]=1.0;
}

void display(void)
{
	rayTracer.castRays();
	drawit();
}

void init(void)
{
	clearFramebuffer();
	antialiasing = false;
	ref_enabled = true;
	spec_enabled = true;

	Light *ambient = new Light(Color(0.7, 0.7, 0.7), VectorPoint());
	Light *light1  = new Light(Color(0.2, 0.2, 0.9), VectorPoint(6, 5, 10));
	Light *light2  = new Light(Color(0.7, 0.7, 0.7), VectorPoint(10, -5, 10));
	Light *light3  = new Light(Color(0.9, 0.2, 0.2), VectorPoint(-7, -2, 10));

	lighting.push_back(ambient);
	lighting.push_back(light1);
	lighting.push_back(light2);
	lighting.push_back(light3);

	Shape *p1 = new Plane(VectorPoint(0, 0, 1), 0,
		Color(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.5), Color(0.2, 0.2, 0.2));
	Shape *p2 = new Plane(VectorPoint(-1, -2, -1), 40,
		Color(0.0, 0.0, 0.0), Color(0.6, 0.3, 0.3), Color(0.2, 0.2, 0.2), 0.5);
	Shape *s1 = new Sphere(VectorPoint(5, 4, 1), 2,
		Color(0.0, 0.0, 0.0), Color(0.1, 0.1, 0.1), Color(0.6, 0.6, 0.6));
	Shape *s2 = new Sphere(VectorPoint(8, 9, 7), 2,
		Color(0.2, 0.0, 0.0), Color(0.5, 0.0, 0.0), Color(0.0, 0.0, 0.9));
	Shape *s3 = new Sphere(VectorPoint(12, 1, 5), 4,
		Color(0.2, 0.2, 0.2), Color(0.5, 0.5, 0.5), Color(0.6, 0.6, 0.6), 0.7);
	Shape *s4 = new Sphere(VectorPoint(4, -3, 3), 1,
		Color(0.2, 0.2, 0.0), Color(0.5, 0.5, 0.0), Color(0.6, 0.6, 0.6));
	Shape *s5 = new Sphere(VectorPoint(-3, -1, 4), 1,
		Color(0.2, 0.2, 0.2), Color(0.3, 0.3, 0.3), Color(0.0, 0.9, 0.0));
	Shape *s6 = new Sphere(VectorPoint(7, -10, 0), 4,
		Color(0.0, 0.2, 0.0), Color(0.0, 0.5, 0.0), Color(0.9, 0.9, 0.9), 0.2);
	Shape *c1 = new Pipe(VectorPoint(-2, 5, 0), 1,// 1, 4,
		Color(0.0, 0.2, 0.2), Color(0.0, 0.5, 0.5), Color(0.9, 0.0, 0.0));

	world.push_back(p1);
	world.push_back(p2);
	world.push_back(s1);
	world.push_back(s2);
	world.push_back(s3);
	world.push_back(s4);
	world.push_back(s5);
	world.push_back(s6);
	world.push_back(c1);

	rayTracer = Tracer(
		VectorPoint(-4, -2, 9),
		VectorPoint(0, -1, 6),
		VectorPoint(0, 0, 1),
		15, 15
	);
}

int main(int argc, char** argv)
{
	init();	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(ImageW, ImageH);
	glutCreateWindow("Nick Barnes - Ray Tracer");

	glutDisplayFunc(display);
	glutMainLoop();
}

