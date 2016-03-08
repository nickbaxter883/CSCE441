#ifndef SHAPE_H
#define SHAPE_H
#include "global.h"
#include "point.h"

class Shape {
protected:
	GLfloat solveQuadratic (GLfloat A, GLfloat B, GLfloat C, bool solNum);
	class NoSolution {};

public:
	//Find the smallest positive parametric parameter
	virtual GLfloat intersection(Ray& r) =0;
	virtual VectorPoint getNormal(VectorPoint& p) =0;

	Color ka, kd, ks;
	GLfloat reflection;
	Shape(): ka(Color()), kd(Color()), ks(Color()), reflection(0.0) {}
	Shape(Color a, Color d, Color s, GLfloat ref = 0.0)
		: ka(a), kd(d), ks(s), reflection(ref) {}
};

class Plane : public Shape {
private:
	//Ax + By + Cz + D = 0
	VectorPoint normal;
	GLfloat d_coeff; 

public:
	Plane():Shape(), normal(VectorPoint()), d_coeff(0) {}
	Plane(VectorPoint p, GLfloat d,
		Color ca, Color cd, Color cs, GLfloat ref = 0.0)
		:Shape(ca, cd, cs, ref), normal(p), d_coeff(d) {}

	GLfloat intersection(Ray& ray);
	VectorPoint getNormal(VectorPoint& p) { return normal.norm(); }
};

class Sphere : public Shape {
private:
	//(x-cx)^2 + (y-cy)^2 + (z-cz)^2 = r^2
	VectorPoint center;
	GLfloat radius;

public:
	Sphere():Shape(), center(VectorPoint()), radius(0.0) {}
	Sphere(VectorPoint p, GLfloat rad,
		Color ca, Color cd, Color cs, GLfloat ref = 0.0)
		:Shape(ca, cd, cs, ref), center(p), radius(rad) {}

	GLfloat intersection(Ray& ray);
	VectorPoint getNormal(VectorPoint& p) { return (p - center).norm(); }
};

class Pipe : public Shape {
private:
	//(x-cx)^2 + (y-cy)^2 = r^2
	VectorPoint center;
	GLfloat radius;//, zmin, zmax;

public:
	Pipe():Shape(), center(VectorPoint()), radius(0.0) {}//, zmin(0.0), zmax(0.0) {}
	Pipe(VectorPoint p, GLfloat rad,// GLfloat min, GLfloat max,
		Color ca, Color cd, Color cs, GLfloat ref = 0.0)
		:Shape(ca, cd, cs, ref), center(p), radius(rad) {}//, zmin(min), zmax(max) {}

	GLfloat intersection(Ray& ray);
	VectorPoint getNormal(VectorPoint& p) {
		return VectorPoint(p.x - center.x, p.y - center.y, 0.0).norm();
	}
};

#endif

