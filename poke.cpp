//Project ID: 5949F553E20B650AB0FB2266D3C0822B13D248B0

#include "pathFinder.h"

using namespace std;

int main(int argc, char* argv[]) {
	path graph;
	cout << setprecision(2);
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
	case algorit::OSTTSP:
		graph.readInputB();
        graph.optTsp();
		break;
	default:
		break;
	}
}