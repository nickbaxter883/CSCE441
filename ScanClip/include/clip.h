
#ifndef CLIP_H 
#define CLIP_H

#include "global.h"
enum Boundary { Left, Right, Bottom, Top };

class Clipper {
public:
	Clipper (Polygon p, Point min, Point max):poly(p), lower(min), upper(max) {}
	Polygon clip();

private:
	Polygon poly;
	Point lower, upper;
	enum Boundary { Left, Right, Bottom, Top };

	void clip_boundary(Boundary b);
	bool inside(Point pt, Boundary b);
	Point intersection(Point p1, Point p2, Boundary b);
};

#endif

