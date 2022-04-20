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
	void upperBoundGen();
	bool promising(size_t permLength);
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
	
	void genPerms(size_t permLength);
private:
	double partialMST(size_t permLength);
	void distTable();
    int numPokemon = 0;
	std::vector<int> path;
	
	std::vector<pokeLocA> Acoords;
	std::vector<Table> prims;

	std::vector<std::pair<int,int>> Bcoords;
	std::vector<int> boundingPath;
	std::vector<std::vector<double>> distanceT;
	double currentCost = 0.0;
	double totalEst = 0.0;
	double bestCost = 0.0;
	double distanceA(int index1, int index2);
	double distanceBC(int index1, int index2);
};

