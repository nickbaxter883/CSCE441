
#include "global.h"
#include <iostream>
#include <fstream>
using namespace std;

vector<Polygon> shapes;
Point clip_min, clip_max;

void load_shapes(string file);

void input()
{
	string file;
	int x1, y1, x2, y2;
	
	cout << "Enter a file to read from: ";
	cin >> file;
	cout << "Trying to load: " << file << endl;
	load_shapes(file);

	cout << "Enter boundaries to clip to: ";
	cin >> x1 >> y1 >> x2 >> y2;
	clip_min = Point(x1, y1);
	clip_max = Point(x2, y2);
}

void load_shapes(string file)
{
	GLchar type;
	GLfloat x, y;
	GLint idx;
	vector<Point> vertex_list;
	Polygon face;

	ifstream fs;
	fs.open(file.c_str());

	if (fs.is_open()) {
		shapes.clear();
		while (fs >> type) {
			if (type == 'v') {
				cout << "found vertex" << endl;
				fs >> x >> y;
				x = ImageW * (x+1) / 2;
				y = ImageH * (y+1) / 2;
				vertex_list.push_back(Point(x, y));		
				cout << "added point: " << x << " " << y << endl;
			}
			else if (type == 'f') {
				cout << "found face" << endl;
				while (fs >> idx) {
					face.add_point(vertex_list[idx-1]);
					cout << idx << " ";
					if (fs.peek() == '\n')
						break;
				}
				cout << endl;
				shapes.push_back(Polygon(face));
				face = Polygon();
			}
		}
	}
	else {
		cout << "Could not open file!\n";
		exit(0);
	}

	fs.close();
}

