#include "point.h"
#include <cmath>

GLfloat VectorPoint::size() {
	return sqrt(this->dotProd(*this));
}

VectorPoint VectorPoint::norm () {
	VectorPoint* p = this;
	GLfloat d = p->size();
	return VectorPoint(p->x/d, p->y/d, p->z/d);
}

VectorPoint VectorPoint::crossProd(VectorPoint point) {
	VectorPoint* p = this;
	return VectorPoint(
		p->y*point.z - p->z*point.y,
		p->z*point.x - p->x*point.z,
		p->x*point.y - p->y*point.x);
}
GLfloat VectorPoint::dotProd(VectorPoint p) {
	return this->x*p.x + this->y*p.y + this->z*p.z;
}

VectorPoint VectorPoint::operator+(VectorPoint p) {
	return VectorPoint (this->x + p.x, this->y + p.y, this->z + p.z);
}

VectorPoint VectorPoint::operator-(VectorPoint p) {
	return VectorPoint (this->x - p.x, this->y - p.y, this->z - p.z);
}

VectorPoint VectorPoint::operator*(GLfloat f) {
	return VectorPoint (f*this->x, f*this->y, f*this->z);
}

std::ostream& operator<<(std::ostream& os, const VectorPoint& p) {
	return os << "(" << p.x << "," << p.y << "," << p.z << ")" << std::endl;
}

VectorPoint Ray::at(GLfloat t) {
	return VectorPoint(
		origin.x + t*direction.x,
		origin.y + t*direction.y,
		origin.z + t*direction.z);
}

