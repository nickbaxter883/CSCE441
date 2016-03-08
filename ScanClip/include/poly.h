
#ifndef POLY_H 
#define POLY_H 

#include <vector>
#include <iostream>
using namespace std;

class Point {
public:
	Point():x(0), y(0) {}
	Point(int x_coord, int y_coord):x(x_coord), y(y_coord) {}

	GLfloat get_x() { return x; }
	GLfloat get_y() { return y; }
	void set_x(GLfloat x_coord) { x = x_coord; }
	void set_y(GLfloat y_coord) { y = y_coord; }

private:
	GLfloat x, y;
};

class Polygon {
public:
	Polygon () {}
	Polygon (const Polygon& p) { verticies = vector<Point>(p.verticies); }
	vector<Point> get_verticies() { return verticies; }

	void add_point(Point pt) { verticies.push_back(pt); }
	void draw() {
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
			for (unsigned int idx = 0; idx < verticies.size(); idx++)
				glVertex2i (verticies[idx].get_x(), verticies[idx].get_y());
		glEnd();
	}
	void print() {
		for (unsigned int idx = 0; idx < verticies.size(); idx++)
			cout << "(" << verticies[idx].get_x()
				 << ", " << verticies[idx].get_y() << ") ";
		cout << endl;
	}

private:
	vector<Point> verticies;
};

#endif

