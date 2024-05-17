#pragma once
#include "Algorithm.h"
#include <vector>
#include <iostream>

#include "GeneticAlgorithm/Population.h"
#include "GeneticAlgorithm/Selection.h"
#include "GeneticAlgorithm/Crossover.h"
#include "GeneticAlgorithm/Mutation.h"

#include <cmath>
#include "OBJFileHandler.h"

class GeneticAlgorithm : public Algorithm
{

public:
	GeneticAlgorithm(const string& filename, int popSize, double probaCross, double probaMut, int maxIter, Selection& selection);
	//GeneticAlgorithm(const string& filename, int popSize, double probaCross, double probaMut, int maxIter);

	void run() override;

	//Getters
	int getPopSize() const;
	int getMaxIteration() const;
	int getDimension() const;
	double getProbaCross() const;
	double getProbaMut() const;
	void printPopulation() const;

	

	// FONCTIONS TYPIQUE DU GA

	//reséparer en , création, initialisation pop, initialisation, tournoi = selection, 
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
	vector<double> d_score_pop;
	

	vector<int> turnamentWinner;

	bool d_popResized = false;

	//-----------------------------

	Population* d_Population;
	Selection* d_Selection;
	Crossover* d_Crossover;
	Mutation* d_Mutation;


};

