#pragma once

#include <vector>
using namespace std;

class Population
{

public: 

	Population(int dimension, int popSize);

	vector<vector<int>> randomInit();


private:

	//Fonction pour génerer un individu
	vector<int> generateRandomIndiv();


	int d_dimension;
	int d_popSize;

};

