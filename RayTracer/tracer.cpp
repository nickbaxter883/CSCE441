#include "tracer.h"
#include <cmath>
#include <limits>
using namespace std;

extern vector<Shape*> world;
extern vector<Light*> lighting;
extern bool antialiasing;
extern bool ref_enabled;
extern bool spec_enabled;

Tracer::Tracer (VectorPoint eye, VectorPoint center, VectorPoint up,
	GLfloat width, GLfloat height): eyePoint(eye) {

	VectorPoint dir = (center - eye).norm();
	VectorPoint newUp = (up - (dir * ( dir.dotProd(up) ))).norm();
	VectorPoint left = newUp.crossProd(dir);

	newUp = newUp * (height/2);
	left = left * (width/2);

	corner = center - newUp + left;
	VectorPoint top = center + newUp + left;
	VectorPoint bottom = center - newUp - left;

	horizSide = bottom - corner;
	vertSide  = top - corner;
}

Tracer::Tracer (VectorPoint eye, VectorPoint c, VectorPoint h, VectorPoint v)
	: eyePoint(eye), corner(c), horizSide(h), vertSide(v) {}

static GLint depth;

VectorPoint Tracer::getTarget(GLint i, GLint j) {
	return corner +	(horizSide * ((GLfloat) i/ImageW)) + (vertSide  * ((GLfloat) j/ImageH ));
}

void Tracer::castRays ()
{
	GLint i, j;
	Color pixle;

	//Iterate over viewplane
	for (j = 0; j < ImageH; j++) {
		for (i = 0; i < ImageW; i++) {

			//Trace ray
			depth = 0;
			if (antialiasing && i != ImageW && j!= ImageH) {
				pixle = 
					(trace(Ray(eyePoint, getTarget(i,j) - eyePoint)) +
					trace(Ray(eyePoint, getTarget(i+0.5, j) - eyePoint)) +
					trace(Ray(eyePoint, getTarget(i, j+0.5) - eyePoint)) +
					trace(Ray(eyePoint, getTarget(i+0.5, j+0.5) - eyePoint)) ) * 0.25;
			}
			else
				pixle = trace(Ray(eyePoint, getTarget(i, j) - eyePoint));

			setFramebuffer(i, j, pixle);
		}
	}
}

Intersection Tracer::getClosest(Ray& ray) {

	GLfloat min_t = numeric_limits<float>::max();
	GLuint obj_idx = world.size();
	
	//Find min intersection
	for (GLuint idx = 0; idx < world.size(); idx++) {
		GLfloat shape_t = world[idx]->intersection(ray);
		if (shape_t == -1)
			continue;

		//Found an intersection
		if (shape_t > 0 && shape_t < min_t) {
			min_t = shape_t;
			obj_idx = idx;
		}
	}

	return Intersection(min_t, obj_idx);
}

VectorPoint reflect(VectorPoint in, VectorPoint norm) {
	return in - (norm * (in.dotProd(norm) * 2));
}

Color Tracer::trace(Ray ray)
{
	Intersection collision = getClosest(ray);
	Color pix_color = Color(0.0, 0.0, 0.0);
	
	//Nothing to render
	if (collision.obj_idx == world.size())
		return pix_color;

	VectorPoint interPoint = ray.at(collision.t_value);
	VectorPoint normal = world[collision.obj_idx]->getNormal(interPoint);

	//Ambient Light 
	Color ambient_component = lighting[0]->color * world[collision.obj_idx]->ka;
	pix_color = pix_color + ambient_component;

	for (GLuint idx = 1; idx < lighting.size(); idx++) {

		Ray secondary(interPoint, lighting[idx]->position - interPoint);
		Intersection shadow = getClosest(secondary);

		//Shadow calculation
		if (shadow.t_value > (lighting[idx]->position - interPoint).size()) {

			GLfloat diff_facing = normal.dotProd(secondary.direction);
			if (diff_facing > 0) {
				//Diffuse calculation
				Color diffuse_component =
					lighting[idx]->color *
					world[collision.obj_idx]->kd *
					diff_facing;
				pix_color = pix_color + diffuse_component;
			
				//Specular calculation
				if (spec_enabled) {
					VectorPoint reflection_dir = reflect(ray.direction, normal);
					GLfloat spec_facing = reflection_dir.dotProd(secondary.direction);
					if (spec_facing > 0) {
						Color specular_component =
							lighting[idx]->color *
							world[collision.obj_idx]->ks *
							pow(spec_facing, 8.0);	//Specular Exp
						pix_color = pix_color + specular_component;
					}
				}
			}
		}
	}

	//Reflection
	GLfloat reflection = world[collision.obj_idx]->reflection;
	if (ref_enabled && reflection) {
		if (depth < 2) {	//Max depth
			depth++;
			Ray bounce(interPoint, reflect(ray.direction, normal));
			return (pix_color * (1-reflection)) +
					(trace(bounce) * reflection);
		}
		depth = 0;
	}

	return pix_color;
}

