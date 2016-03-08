#ifndef TRACER_H
#define TRACER_H
#include "global.h"
#include "point.h"
#include "shape.h"

struct Intersection {
	GLfloat t_value;
	GLuint  obj_idx;
	Intersection(GLfloat t, GLuint o): t_value(t), obj_idx(o) {}
};

struct Tracer {
	
	Tracer (): eyePoint(VectorPoint()), corner(VectorPoint()),
			horizSide(VectorPoint()), vertSide(VectorPoint()) {}

	//Nicer specification
	Tracer (VectorPoint eye, VectorPoint center, VectorPoint up,
		GLfloat width, GLfloat height);

	void castRays();

private:
	VectorPoint eyePoint, corner, horizSide, vertSide;

	//Easy to interpolate
	Tracer (VectorPoint eye, VectorPoint c, VectorPoint h, VectorPoint v);
	VectorPoint getTarget(GLint i, GLint j);
	Intersection getClosest(Ray& ray);
	
	Color trace(Ray r);
};

#endif

