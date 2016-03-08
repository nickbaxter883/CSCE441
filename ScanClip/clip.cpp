
#include "clip.h"

Polygon Clipper::clip() {
	clip_boundary(Left);
	clip_boundary(Right);
	clip_boundary(Bottom);
	clip_boundary(Top);
	return poly;
}

void Clipper::clip_boundary(Boundary b) {
	Polygon clipped;
	Point p1, p2;
	for (unsigned int idx = 0; idx < poly.get_verticies().size(); idx++) {
		p1 = poly.get_verticies()[idx];
		if (idx == poly.get_verticies().size()-1)
			p2 = poly.get_verticies()[0];
		else
			p2 = poly.get_verticies()[idx+1];

		if (inside(p2, b)) {
			if (!inside(p1, b)) {
				clipped.add_point(intersection(p1, p2, b));
				clipped.add_point(p2);
				cout << "out->in ";
			}
			else {
				clipped.add_point(p2);
				cout << "in->in ";
			}
		}
		else if(inside(p1, b)) {
			clipped.add_point(intersection(p1, p2, b));
			cout << "in->out ";
		}
		else cout << "out->out ";

		//clipped.print();
	}

	cout << endl;
	poly = clipped;
	poly.print();
}

bool Clipper::inside(Point pt, Boundary b) {
	switch (b) {
		case Left:	 return (pt.get_x() >= lower.get_x());
		case Right:	 return (pt.get_x() <= upper.get_x());
		case Bottom: return (pt.get_y() >= lower.get_y());
		case Top:	 return (pt.get_y() <= upper.get_y());
	}
}

Point Clipper::intersection(Point p1, Point p2, Boundary b) {
	Point intersection;
	GLfloat m = (p1.get_y() - p2.get_y()) / (p1.get_x() - p2.get_x());
	switch (b) {
		case Left:
			intersection.set_x( lower.get_x() );
			intersection.set_y( p2.get_y() + (lower.get_x() - p2.get_x()) * m );
			break;
		case Right:
			intersection.set_x( upper.get_x() );
			intersection.set_y( p2.get_y() + (upper.get_x() - p2.get_x()) * m );
			break;
		case Bottom:
			intersection.set_y( lower.get_y() );
			intersection.set_x( p2.get_x() + (lower.get_y() - p2.get_y()) / m );
			break;
		case Top:
			intersection.set_y( upper.get_y() );
			intersection.set_x( p2.get_x() + (upper.get_y() - p2.get_y()) / m );
			break;
	}
	return intersection;
}

