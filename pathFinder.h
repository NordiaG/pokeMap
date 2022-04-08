//Project ID: 5949F553E20B650AB0FB2266D3C0822B13D248B0

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <getopt.h>
#include <cmath>

enum class algorit {
	MST = 0,
	FASTTSP,
	OPTTSP
};

class path{
public:
    void getOptions(int &argc, char ** &argv);
    void readInputA();
    void readInputB();
    double distanceHelper(int index1, int index2);
    void mst();
    void fastTsp();
    void optTsp();
    algorit mode = algorit::MST;

    struct pokeLocA {
		std::pair<int, int> coords;
		char loc; //where in the world: water, land, or border
		pokeLocA():loc('\0') {}
		pokeLocA(std::pair<int, int> temp) : coords(temp), loc('\0') {}
		pokeLocA(std::pair<int, int> coord, char temp) : coords(coord), loc(temp) {}
	};
	struct Table {
		double distance;
		bool table;
		int32_t previous;
		
		Table(): distance(INFINITY), table(false), previous(0) {}
	};

private:
    int numPokemon = 0;
	std::vector<int> path;
	std::vector<pokeLocA> Acoords;
	std::vector<Table> prims;
	std::vector<std::pair<int,int>> Bcoords;
	double currentCost;
	double distanceA(int index1, int index2);
	double distanceBC(int index1, int index2);
};