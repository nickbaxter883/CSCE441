
#include "scan.h"
#include <vector>
using namespace std;

void Scanner::scan()
{
	cout << endl;
	construct_AET();
	
	list<Edge> AEL;
	list<Edge>::iterator iter, edge1, edge2, temp;
	unsigned int num_edges = 0;
	bool flag = false;

	for (int idy = 0; idy <= ImageH; idy++) {
		//Add edges
		iter = AET[idy].begin();
		while (iter != AET[idy].end()) {
			//Add sorted
			add_sorted(*iter, AEL);
			iter++;
		}

		if ((AEL.size() != num_edges) && (AEL.size() != 0)) {
			flag = true;
			cout << "\nline " << idy << " " << AEL.size() << ": ";
			num_edges = AEL.size();
		}

		//Remove edges
		iter = AEL.begin();
		while (iter != AEL.end()) {
			if (iter->max_y == idy) {
				AEL.erase(iter);
				iter--;
			}
			iter++;
		}
		//Scan Line
		//AEL contains pairs of edges
		iter = AEL.begin();
		while (iter != AEL.end()) {
			edge1 = iter;	iter++;
			edge2 = iter;	iter++;
			//Hack fix for order of edges
			if (edge1->curr_x > edge2->curr_x) {
				temp = edge1;
				edge1 = edge2;
				edge2 = temp;
			}
			if (flag == true) 
				cout << edge1->curr_x << "->" << edge2->curr_x << " ";

			for (int idx = edge1->curr_x; idx < edge2->curr_x; idx++) {
				screen.setFramebuffer(idy, idx);
			}
			edge1->curr_x += edge1->inv_sl;
			edge2->curr_x += edge2->inv_sl;
		}
		flag = false;
	}
	cout << endl;
}

void Scanner::construct_AET()
{
	cout << "constructing\n";
	Point curr, adj1, adj2;
	vector<Point> verticies = poly.get_verticies();

	int size = verticies.size();
	//Iterate through polygon verticies finding adjacent ones
	for (int idx = 0; idx < size; idx++) {
		curr = verticies[idx];
		adj1 = verticies[(idx+size-1)%size];
		adj2 = verticies[(idx+1)%size];

		//Make edges well ordered
		if (adj1.get_x() > adj2.get_x())
			swap(adj1, adj2);

		cout << "checking vert " << idx << ": (" << curr.get_x() << ", " << curr.get_y() << ")\n";

		//Insert edges into scanline sorted by x value
		if (adj1.get_y() > curr.get_y()) {
			Edge side (curr, adj1);
			add_sorted(side, AET[curr.get_y()]);
			cout << "added edge on " << side.min_y << ": max y " << side.max_y
				 << ", curr x " << side.curr_x << ", inv_sl " << side.inv_sl << endl;
		}
		//Repeat for other edge
		if (adj2.get_y() > curr.get_y()) {
			Edge side (curr, adj2);
			add_sorted(side, AET[curr.get_y()]);
			cout << "added edge on " << side.min_y << ": max y " << side.max_y
				 << ", curr x " << side.curr_x << ", inv_sl " << side.inv_sl << endl;
		}
	}
}

void swap(Point& pt1, Point& pt2)
{
	Point temp = pt1;
	pt1 = pt2;
	pt2 = temp;
}

void Scanner::add_sorted(Edge& e, list<Edge>& l)
{
	list<Edge>::iterator iter = l.begin();
	while((iter != l.end()) && (iter->curr_x <= e.curr_x)) { iter++; }

	l.insert(iter, e);
}

Scanner::Edge::Edge (Point pt1, Point pt2)
{
	max_y = pt2.get_y();
	min_y = pt1.get_y();
	curr_x = pt1.get_x();
	inv_sl = (pt1.get_x()-pt2.get_x()) / (pt1.get_y()-pt2.get_y());
}

