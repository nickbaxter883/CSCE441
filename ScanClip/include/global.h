
#ifndef MAIN_H
#define MAIN_H

#include <GL/glut.h>
#include "frame.h"
#include "poly.h"

extern Frame screen;
extern std::vector<Polygon> shapes;
extern Point clip_min, clip_max;

void input();

#endif

