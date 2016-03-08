
#ifndef POINT_H 
#define POINT_H
#include <GL/glut.h>
#include <cmath>

struct Point {

    Point():x(0), y(0), z(0) {}
    Point(GLfloat x_coord, GLfloat y_coord, GLfloat z_coord)
		:x(x_coord), y(y_coord), z(z_coord) {}

	Point norm () {
		GLfloat d = sqrt(pow(this->x, 2.0) + pow(this->y, 2.0) + pow(this->z, 2.0));
		return Point(this->x/d, this->y/d, this->z/d);
	}

	Point crossProd(Point p) {
		return Point(this->y*p.z - this->z*p.y,
					 this->z*p.x - this->x*p.z,
					 this->x*p.y - this->y*p.x);
	}
	GLfloat dotProd(Point p) {
		return this->x*p.x + this->y*p.y + this->z*p.z;
	}

    GLfloat x, y, z;
};

Point operator+(Point p1, Point p2) {
	return Point (p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

Point operator-(Point p1, Point p2) {
	return Point (p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

Point operator*(GLfloat f, Point p) {
	return Point (f*p.x, f*p.y, f*p.z);
}

#endif

