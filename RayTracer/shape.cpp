#include "shape.h"
#include <cmath>

//0.1 for round off error
GLfloat threshold = 0.01;

GLfloat Shape::solveQuadratic (GLfloat A, GLfloat B, GLfloat C, bool solNum)
{
	GLfloat discriminant = pow(B, 2.0) - 4*A*C;
	if (discriminant < 0)
		throw Shape::NoSolution();

	if (solNum == true)
		return (-B + sqrt(discriminant)) / (2*A);

	return (-B - sqrt(discriminant)) / (2*A);
}


//A ray can intersect a plane in only one location or is parallel
//A(x0+dxt) + B(y0+dyt) + C(z0+dzt) + D = 0
//(Ax0 + By0 + Cz0) + t(Adx + Bdy + Cdz) + D = 0

GLfloat Plane::intersection(Ray& ray) {

	GLfloat t_coeff = normal.dotProd(ray.direction);
	if (t_coeff == 0) //direction is parallel to plane
		return -1;

	GLfloat solution = (normal.dotProd(ray.origin) + d_coeff)/(-t_coeff);

	//Dont see it
	if (solution <= threshold) 
		return -1;

	return solution;
}

//A ray can intersect a sphere in two locations, not at all, or is tangent
//(x0+dxt-cx)^2 + (y0+dyt-cy)^2 + (z0+dzt-cz)^2 = r^2
//
//All squared terms in expanded form will combine into squared moduli
//	which are a dot prod with self
//A t^2 can be factored from the direction dot product
//The doubled terms are of the form
//	2v0*dvt - 2dvt*cv - 2v0*cv where v is x,y,z
//
//In the quadratic form At^2 + Bt + C = 0 we have:
//A = dir dot dir
//B = 2*sum[ dv(v0-cv) ] for v=x,y,z
//C = (orig dot orig) + (c dot c) - r^2 - 2*sum[ v0cv ] for v=x,y,z

GLfloat Sphere::intersection(Ray& ray) {

	GLfloat A = ray.direction.dotProd(ray.direction);

	GLfloat B =	2*(
		ray.direction.x * (ray.origin.x - center.x) +
		ray.direction.y * (ray.origin.y - center.y) +
		ray.direction.z * (ray.origin.z - center.z) );

	GLfloat C =
		ray.origin.dotProd(ray.origin) +
		center.dotProd(center) -
		pow(radius, 2.0) - 2*(
			ray.origin.x * center.x +
			ray.origin.y * center.y +
			ray.origin.z * center.z );
	
	try {
		GLfloat t1, t2;
		t1 = solveQuadratic (A, B, C, 0);
		t2 = solveQuadratic (A, B, C, 1);

		//Sphere is behind us
		if (t1 <= threshold && t2 <= threshold)
			return -1;
		//Outside Sphere
		else if (t1 > threshold && t2 > threshold)
			return (t1 < t2) ? t1 : t2;
		//Inside sphere, return the positive ans
		else if (t1 > t2)
			return t1;
		else
			return t2;
	}
	//Did not intersect sphere
	catch (NoSolution) {
		return -1;
	}
	
	//Logic Error
	return -2;
}

//Very similar to Sphere
//A ray can intersect a pipe in two locations, not at all, or is tangent
//(x0+dxt-cx)^2 + (y0+dyt-cy)^2 = r^2
//
//A t^2 can be factored from the direction dot product
//The doubled terms are of the form
//	2v0*dvt - 2dvt*cv - 2v0*cv where v is x,y
//
//In the quadratic form At^2 + Bt + C = 0 we have:
//A = dir dot dir - dz^2
//B = 2*sum[ dv(v0-cv) ] for v=x,y
//C = (orig dot orig)-z0^2 + (c dot c)-cz^2 - r^2 - 2*sum[ v0cv ] for v=x,y

GLfloat Pipe::intersection(Ray& ray) {

	GLfloat A = ray.direction.dotProd(ray.direction) -
				pow(ray.direction.z, 2.0);

	GLfloat B =	2*(
		ray.direction.x * (ray.origin.x - center.x) +
		ray.direction.y * (ray.origin.y - center.y));

	GLfloat C =
		ray.origin.dotProd(ray.origin) - pow(ray.origin.z, 2.0) +
		center.dotProd(center) - pow(center.z, 2.0) -
		pow(radius, 2.0) - 2*(
			ray.origin.x * center.x +
			ray.origin.y * center.y);
	
	try {
		GLfloat t1, t2;
		t1 = solveQuadratic (A, B, C, 0);
		t2 = solveQuadratic (A, B, C, 1);

		//Pipe is behind us
		if (t1 <= threshold && t2 <= threshold)
			return -1;
		//Pass over top or bottom
		//else if ((t1 > zmax && t2 > zmax) || (t1 < zmin && t2 < zmin))
			//return -1;

		//Outside Pipe
		else if (t1 > threshold && t2 > threshold) {
			return (t1 < t2) ? t1 : t2;
		}
		//Inside Pipe, return the positive ans
		else if (t1 > t2)
			return t1;
		else
			return t2;
	}
	//Did not intersect pipe 
	catch (NoSolution) {
		return -1;
	}
	
	//Logic Error
	return -2;
}

