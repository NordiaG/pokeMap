//Project ID: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#include <pathFinder.h>
using namespace std;

double path::distanceHelper(int c1, int c2) {
	if (mode == algorit::MST) {
		return distanceA(c1, c2);
	}
	return distanceBC(c1, c2);
}

double path::distanceA(int i1, int i2){
	cageA c1 = Acoords[i1];
	cageA c2 = Acoords[i2];
	if ((c1.loc == 'w' && c2.loc == 's') || (c1.loc == 's' && c2.loc == 'w')) {
		return INFINITY;
	}
	else {
		double x1 = c1.coords.first, x2 = c2.coords.first,
		y1 = c1.coords.second, y2 = c2.coords.second;
		double dist = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
		return dist;
	}
}

double path::distanceBC(int i1, int i2) {
	pair<int,int> c1 = Bcoords[i1];
	pair<int,int> c2 = Bcoords[i2];
	double x1 = c1.first, x2 = c2.first,
	 y1 = c1.second, y2 = c2.second;
	double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return dist;
}

void path::getOptions(int argc, char** argv) {
	opterr = false;
	int optionIndex = 0, optionChoosen = 0;
	struct option longOpts[] = {
		{nullptr, 0, nullptr, '\0'},
		{"mode", required_argument, nullptr, 'm'},
		{"help", no_argument, nullptr, 'h'},
	};
	while ((optionChoosen = getopt_long(argc, argv, "hm:", longOpts,
		&optionIndex)) != -1) {
		string temp = optarg;  
		switch (optionChoosen) {
		case 'm':
			if (temp == "MST") {
				mode = algorit::MST;
			}
			else if (temp == "FASTTSP") {
				mode = algorit::FASTTSP;
			}
			else if (temp == "OSTTSP") {
				mode = algorit::OSTTSP;
			}
			else {
				cerr << "Invalid mode entered";
				exit(1);
			}
			break;
		case 'h':
			cout << "You are a zookeeper for lots of animals, you plan to feed\n"
				<< "each animal and construct water canals to give water.\n"
				<< "This program will help find the most efficient routes.\n"
				<< "Mode A is only for creating a path to feed them.\n"
				<< "In modes B and C is constructing the canal efficiently\n"
				<< "so the canal will be a cycle. Mode B is more about speed,\n"
				<< "mode C is more about an optimal path.\n"
				<< "Usage: \'./zoo\n\t[--mode| -m]<A: MST, B: FASTTSP, C: OSTTSP>\n"
				<< "\t[--help | -h]";
			exit(0);
		default:
			cerr << "Error: invalid option\n";
			break;
		}//switch
	}//while
}