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

	//Getters
	int getPopSize() const;
	int getMaxIteration() const;
	int getDimension() const;
	double getProbaCross() const;
	double getProbaMut() const;
	void printPopulation() const;

	void exportBest();

	// FONCTIONS TYPIQUE DU GA

	//res�parer en , cr�ation, initialisation pop, initialisation, tournoi = selection, 
	// croisements, mutation, fonction de check de critere d'arret

	//void createPop();
	//void initializePop();
	
	//renvoie les 2 winners
	 //vector<int>* turnament();

	 //void crossover();
	 //void mutation();

	 //surement mettre en private ses trucs la

	 //void onePointCrossover(int first_parent, int sec_parent);
	 //void oneGeneMutation(int child);




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
	

	vector<int> turnamentWinner;
	vector<int> parents;

	bool d_popResized = false;

	//-----------------------------

	Population* d_Population;
	Selection* d_Selection;
	Crossover* d_Crossover;
	Mutation* d_Mutation;

private:
	/**
	 * Chemin du repertoire ves lequel l'agoritme ecrit
	 * les solutions trouvees sous forme de fichiers .obj
	*/
	static const string GENERATE_OBJ_PATH;
	
	vector<Polyedre> perm2Poly(int index);
	vector<Polyedre> d_permutScoreMax;
	double d_scoreMax=0.0;

};

