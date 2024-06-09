#pragma once

#include <vector>

using namespace std;

/**
 * @brief Classe abstraite de croisement avec la fonction cross a redefinir
 */
class Crossover
{

public:

	/**
	 * @brief Croisement abstrait de 2 individus
	 * 
	 * Effectue le croisement des 2 parent et modifie
	 * les enfants en parametres en consequence
	 *
	 * @param parent1
	 * @param parent2
	 * @param child1 Enfant vide
	 * @param child2 Enfant vide
	*/
	virtual void cross(
		const vector<int>& parent1, 
		const vector<int>& parent2,
		vector<int>& child1,
		vector<int>& child2
	) = 0;
};

