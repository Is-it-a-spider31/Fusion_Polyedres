#pragma once

#include "Crossover.h"

/**
 * @brief Permet de faire un croisement en N points 
*/
class NXCrossover : public Crossover
{
public:

	/**
	 * @brief Constructeur
	 * 
	 * @param nbPoints Nombre de points de croisement
	*/
	NXCrossover(int nbPoints);

	/**
	 * @brief Croisement en N points de 2 individus
	 * 
	 * @param parent1 
	 * @param parent2 
	 * @param child1 
	 * @param child2 
	*/
	void cross(
		const vector<int>& parent1, 
		const vector<int>& parent2,
		vector<int>& child1,
		vector<int>& child2
	) override;

	void test();

private:

	/**
	 * @brief Nombre de points de croisement
	*/
	int d_nbCrossoverPoints;

	vector<int> chooseCrossoverPoints(int& size);

	void crossOneChild(
		const vector<int>& parent1,
		const vector<int>& parent2,
		vector<int>& child,
		vector<int> crossoverPoints
	);
};

