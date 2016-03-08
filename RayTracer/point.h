#ifndef POINT_H 
#define POINT_H
#include <GL/glut.h>
#include <iostream>

struct VectorPoint {
    GLfloat x, y, z;

    VectorPoint() : x(0), y(0), z(0) {}
    VectorPoint(GLfloat x_coord, GLfloat y_coord, GLfloat z_coord)
		:x(x_coord), y(y_coord), z(z_coord) {}

	//Useful vector operations
	GLfloat size();
	VectorPoint norm ();
	VectorPoint crossProd(VectorPoint p);
	GLfloat dotProd(VectorPoint p);

	VectorPoint operator+(VectorPoint p);
	VectorPoint operator-(VectorPoint p);
	VectorPoint operator*(GLfloat f);
};

std::ostream& operator<<(std::ostream& os, const VectorPoint& p);

struct Ray {
	//x = x0 + dx*t
	VectorPoint origin, direction;

	Ray() : origin(VectorPoint()), direction(VectorPoint()) {}
	Ray(VectorPoint o, VectorPoint d) : origin(o), direction(d.norm()) {}

	VectorPoint at(GLfloat t);
};

#endif

