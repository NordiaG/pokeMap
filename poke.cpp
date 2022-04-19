//Project ID: 5949F553E20B650AB0FB2266D3C0822B13D248B0

#include "pathFinder.h"

using namespace std;

int main(int argc, char* argv[]) {
	path graph;
	cerr << fixed << showpoint << setprecision(2);
	cout << setprecision(2) << boolalpha;
	cout << fixed;
	graph.getOptions(argc, argv);

	switch (graph.mode){
	case algorit::MST:
		graph.readInputA();
		graph.mst();
		break;
	case algorit::FASTTSP:
		graph.readInputB();
		graph.fastTsp();
		break;
	case algorit::OPTTSP:
		graph.readInputB();
        graph.optTsp();
		break;
	default:
		break;
	}
}