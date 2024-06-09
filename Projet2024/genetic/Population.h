#pragma once

#include <vector>
using namespace std;

/**
 * @brief Classe qui regroupe diverse m�thode d'initialisation de population
 */
class Population
{

public: 

	Population(int dimension, int popSize);

	/**
	 * @brief Initialisation de la population al�atoirement
	 * @return la population initialis�
	 */
	vector<vector<int>> randomInit();


private:

	/**
	 * @brief Genere un individu (permuation) al�atoire sans conflits (pas de doublons de g�ne)
	 * @return un individu sans conflits
	 */
	vector<int> generateRandomIndiv();

	/**
	 * @brief nombre de gene dans un individu
	 */
	int d_dimension;

	/**
	 * @brief taille de la population
	 */
	int d_popSize;

};

