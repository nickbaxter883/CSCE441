
#ifndef SCAN_H
#define SCAN_H

#include "global.h"
#include <list>

class Scanner {
public:
	Scanner (Polygon p):poly(p) {
		AET = vector<list<Edge> >(ImageH+1);
	}
	void scan();

private:
	Polygon poly;
	struct Edge {
	public:
		Edge () {}
		Edge (Point pt1, Point pt2);

		int max_y, min_y;
		float curr_x;
		float inv_sl;
	};

	std::vector<std::list<Edge> > AET;
	void construct_AET();
	void add_sorted(Edge& e, list<Edge>& l);
};

#endif

