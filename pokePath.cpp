//Project ID: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#include "pathFinder.h"
using namespace std;

void path::getOptions(int &argc, char** &argv){
    opterr = false;
	int optionIndex = 0, optionChoosen = 0;
	string temp = "";
	struct option longOpts[] = { 
		{"help", no_argument, nullptr, 'h' },
        {"mode", required_argument, nullptr, 'm'},
        { nullptr, 0, nullptr, '\0' }
    };
	while ((optionChoosen = getopt_long(argc, argv, "hm:", longOpts,
											&optionIndex)) != -1) {
		switch (optionChoosen) {
		case 'm':
			temp = optarg;
            if(temp == "MST"){
                mode = algorit::MST;
            }
			else if(temp == "FASTTSP"){
				mode = algorit::FASTTSP;
			}
			else if(temp == "OPTTSP"){
				mode = algorit::OPTTSP;
			}
			else{
				cerr << "Invalid argument to --captain";
                exit(1);
			}
			break;
        case 'h':
            cout
			<< "Usage: \'./poke\n\t[--mode| -m] <MST|FASTTSP,OSTTSP>\n"
			<< "\t[--help | -h]";
			exit(0);
		default:
			cerr << "Error: invalid option\n";
            return;
		}//switch
	}//while
}

double path::distanceHelper(int c1, int c2) {
	if (mode == algorit::MST) {
		return distanceA(c1, c2);
	}
	return distanceBC(c1, c2);
}

double path::distanceA(int i1, int i2){
	pokeLocA c1 = Acoords[i1];
	pokeLocA c2 = Acoords[i2];
    
	if ((c1.loc == 'w' && c2.loc == 'l') || (c1.loc == 'l' && c2.loc == 'w')) {
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

void path::readInputA(){
	cin >> numPokemon;
	Acoords.reserve(numPokemon);
	pair<int, int> coor;
	char temp;
	for(int i = 0; i < numPokemon; ++i){
		cin >> coor.first;
		cin >> coor.second;
		if (coor.first < 0 && coor.second < 0) {
			temp = 'w';
		}
		else if ((coor.first == 0 && coor.second <= 0) ||
		 (coor.second == 0 && coor.first <= 0)) {
			temp = 'b';
		}
		else {
			temp = 'l';
		}
		Acoords.push_back(pokeLocA(coor,temp));
	}
}

void path::readInputB(){
	cin >> numPokemon;
	Bcoords.reserve(numPokemon);
	pair<int, int> coor;
	for(int i = 0; i < numPokemon; ++i){
		cin >> coor.first;
		cin >> coor.second;
		Bcoords.push_back(coor);
	}
}

void path::mst() {
	prims.resize(numPokemon, Table());
	prims[0].distance = 0;
	currentCost = 0;
	for (int i = 0; i < numPokemon; ++i) {
		int minIndex = -1;
		double min = INFINITY;
		for (int j = 0; j < numPokemon; ++j) {			
			double temp = prims[j].distance;
			if (temp < min && !prims[j].table) {
				min = temp;
				minIndex = j;
			}
		}
		if (min == INFINITY) {
			cerr << "Cannot construct MST";
			exit(1);
		}
		prims[minIndex].table = true;
		currentCost += sqrt(min);
		for (int k = 0; k < numPokemon; ++k) {
			if (!prims[k].table) {
				double d = distanceA(minIndex, k);
				if (d < prims[k].distance) {
					prims[k].distance = d;
					prims[k].previous = minIndex;
				}
			}
		}
	}
	cout << currentCost << "\n";
	for (int i = 1; i < numPokemon; ++i) {
		if (i < prims[i].previous) {
			cout << i << " " << prims[i].previous << "\n";
		}
		else {
			cout << prims[i].previous << " " << i << "\n";
		}
	}
}

void path::fastTsp(){
	path.reserve(numPokemon); 
	path.push_back(0);
	path.push_back(1);
	path.push_back(2);
	int minIndex = 0;
	currentCost = distanceHelper(0,1) + distanceHelper(1,2) + distanceHelper(2,0);
	for(int k = 3; k < numPokemon; ++k){
		double min = INFINITY;
		for(int i = 0; i < (int)path.size()-1; ++i){
			if(distanceBC(i,k) + distanceBC(k,path[i]) - distanceBC(i,path[i]) < min){
				min = distanceBC(i,k) + distanceBC(k,path[i]) - distanceBC(i,path[i]);
				minIndex = i + 1;
			}
		}
		currentCost += min;
		path.insert(path.begin() + minIndex, k);
	}
	cout << currentCost << '\n';
	for(int i = 0; i < numPokemon; ++i){
		cout << path[i] << ' ';
	}
	//check weight
}

void path::upperBoundGen(){
	path.reserve(numPokemon); 
	path.push_back(1);
	path.push_back(2);
	path.push_back(0);
	int minIndex = 0;
	bestCost = distanceHelper(0,1) + distanceHelper(1,2) + distanceHelper(2,0);
	for(int k = 3; k < numPokemon; ++k){
		double min = INFINITY;
		for(int i = 0; i < (int)path.size()-1; ++i){
			if(distanceHelper(i,k) + distanceHelper(k,path[i]) - distanceBC(i,path[i]) < min){
				min = distanceHelper(i,k) + distanceHelper(k,path[i]) - distanceBC(i,path[i]);
				minIndex = i;
			}
		}
		bestCost += min;
		path.resize(path.size()+1);
		path[k] = path[minIndex];
		path[minIndex] = k;
	}
}

double path::partialMST(size_t permLength){
	int newSize = numPokemon - (int)permLength;
	prims.clear();
	prims.resize(newSize, Table());
	prims[0].distance = 0;
	double partialCost = 0.0;
	for (int i = 0; i < newSize; ++i) {
		int minIndex = -1;
		double min = INFINITY;
		for (int j = 0; j < newSize; ++j) {			
			double temp = prims[j].distance;
			if (temp < min && !prims[j].table) {
				min = temp;
				minIndex = j;
			}
		}//min index + weight finder
		prims[minIndex].table = true;
		partialCost += min;
		for (int k = 0; k < newSize; ++k) {
			if (!prims[k].table){
				double d = distanceT[minIndex+permLength][k+permLength];
				if (d < prims[k].distance) {
					prims[k].distance = d;
					prims[k].previous = minIndex;
				}
			}
		}
	}
	return partialCost;
}

bool path::promising(size_t permLength){
	double mstCost= 0.0;  
	currentCost = 0.0;
	bool promise = true;
	double arm1Len = INFINITY, arm2Len = INFINITY;
	int i = 0;
	for(size_t j = 0; j < permLength - 1; ++j){
		currentCost += distanceT[i][path[i]];
		i = path[i];
	}

	for(size_t i = permLength; i < (size_t)numPokemon; ++i){
		if(distanceT[path[0]][path[i]] < arm1Len){
			arm1Len = distanceT[path[0]][path[i]];
		}
		if(distanceT[path[permLength-1]][path[i]] < arm2Len){
			arm2Len = distanceT[path[permLength-1]][path[i]];
		}
	}

	mstCost = partialMST(permLength);
	double totalEst = currentCost + mstCost + arm1Len + arm2Len;
	int start = 0;
	do {
    	cerr << start << ' ';
    	start = path[start];
	} while (start != 0);//change to normal path instead of linked node path
	
	cerr << setw(4) << permLength << setw(10) << currentCost;
	cerr << setw(10) << arm1Len << setw(10) << arm2Len;
	cerr << setw(10) << mstCost << setw(10) << totalEst << "  " << promise << '\n';

	if(totalEst > bestCost){
		return !promise;
	}
	return promise;
}

void path::distTable(){
	distanceT.resize(numPokemon, vector<double>(numPokemon));
	for(int i = 0; i < numPokemon; ++i){
		for(int j = 0; j < i; ++j){
			double dist = distanceBC(i,j);
			distanceT[i][j] = dist;
			distanceT[j][i] = dist;
		}
	}
}

void path::genPerms(size_t permLength) {//change to normal path from linked node path
	if (permLength == path.size()) {
		double weight = currentCost + distanceT[path[permLength-1]][path[0]];
		if(weight < bestCost){
			bestCost = weight;
			boundingPath = path;
		}
	}
	if (!promising(permLength))
		return;
	for (size_t i = permLength; i < path.size(); ++i) {
		swap(path[permLength],path[i]);
		currentCost += distanceT[i][permLength];

		genPerms(permLength + 1);
		
		currentCost -= distanceT[i][permLength]; //swap back
		swap(path[permLength],path[i]);
	}
}

void path::optTsp(){//change to normal path from linked node path
	upperBoundGen();
	path = {1,2,3,4,5,6,7,8,9,10,0};
	bestCost = 336.74;
	boundingPath = path;
	distTable();
	genPerms(1);
	int start = 0;
	double cost = 0.0;
	do {
		cost += distanceT[start][path[start]];
		start = path[start];
	}while(start != 0);
	cout << cost << '\n';

	do {
    	cout << start << ' ';
    	start = boundingPath[start];
	} while (start != 0);
	
}