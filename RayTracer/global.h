#ifndef GLOBAL_H
#define GLOBAL_H

#include <GL/glut.h>
#include <vector>
#include <iostream>
#include "point.h"
using namespace std;

#define ImageW 600
#define ImageH 600

struct Color {
	float r, g, b;		// Color (R,G,B values)

	Color():r(0), g(0), b(0) {}
	Color(GLfloat red, GLfloat green, GLfloat blue)
		:r(red), g(green), b(blue) {}

	Color operator+(Color c) {
		return Color(this->r + c.r, this->g + c.g, this->b + c.b);
	}
	Color operator*(Color c) {
		return Color(this->r * c.r, this->g * c.g, this->b * c.b);
	}
	Color operator*(GLfloat f) {
		return Color(this->r * f, this->g * f, this->b * f);
	}
};

struct Light {
	//All lights have same ambient color
	//Each light has same color for diffuse and specular
	Color color;
	VectorPoint position;
	Light (Color c, VectorPoint p): color(c), position(p) {}
};

void setFramebuffer(int x, int y, Color c);

#endif

