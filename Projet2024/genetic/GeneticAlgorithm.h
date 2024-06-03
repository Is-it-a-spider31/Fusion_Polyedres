#pragma once
#include "../Algorithm.h"
#include <vector>
#include <iostream>

#include "Population.h"
#include "Selection.h"
#include "Crossover.h"
#include "Mutation.h"

#include <cmath>
#include "../OBJFileHandler.h"

using namespace std;

class GeneticAlgorithm : public Algorithm
{

public:
	GeneticAlgorithm(const string& filename, int popSize, double probaCross, double probaMut, int maxIter, Selection& selection, Crossover& crossover, Mutation& mutation);
	//GeneticAlgorithm(const string& filename, int popSize, double probaCross, double probaMut, int maxIter);

	void run() override;
	void printPopulation() const;

	void exportBest();

	/**
	 * Chemin du repertoire ves lequel l'agoritme ecrit
	 * les solutions trouvees sous forme de fichiers .obj
	*/
	const string getFilePath() override;

protected:

	int d_popSize;

	//nb de polyhedre totale
	int d_dimension;
	int d_maxIteration;
	
	double d_crossoverProba;
	double d_mutationProba;

	vector<vector<int>> d_pop;
	vector<vector<int>> d_oldpop;


	vector<double> d_score_pop;
	vector<double> d_oldscore_pop;
	

	//vector<int> turnamentWinner;
	vector<int> parents;

	bool d_popResized = false;

	//-----------------------------

	Population* d_Population;
	Selection* d_Selection;
	Crossover* d_Crossover;
	Mutation* d_Mutation;

private:	

	void printDataChart(const string& info);
	
	vector<Polyedre> perm2Poly(int index);
	vector<Polyedre> d_permutScoreMax;

};

