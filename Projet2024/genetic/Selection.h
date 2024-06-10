#pragma once

#include <vector>
#include <random>
#include <iostream>

using namespace std;

/**
 * @brief Classe de sélection abstraite contenant la méthode select a redefinir ainsi que la liste des parents
 */

class Selection
{
public:

	/**
 * @brief Sélectionne des individus dans la population.
 *
 *  Sélectionne des individus de la population et doit remplir la liste de parents d_parents
 *
 * @param population La population à partir de laquelle sélectionner.
 * @param score Les scores associés à chaque individu de la population.
 */
	virtual void select(vector<vector<int>>& population, vector<double> score) = 0;
	
	/**
	 * @brief Récupère le premier parent individuel
	 * @return Le premier parent
	 */
	vector<int> getParent1() const;

	/**
	 * @brief Récupère le deuxième parent individuel
	 * @return Le premier parent
	 */
	vector<int> getParent2() const;

	/**
	 * @brief Récupere la liste des parents 
	 * @return La liste des parents
	 */
	vector<vector<int>> getParents() const;

	/**
	 * @brief Vide la liste des parents
	 */
	void clearParentsList();

protected:

	/**
	 * @brief Stocke le premier parent
	 * N'est pas utilisé, mais êst prévu pour des sélections nécessitant 
	 * les deux parents individuellement
	 */

	vector<int> d_parent_1;

	/**
	 * @brief Stocke le deuxième parent
	 * N'est pas utilisé, mais êst prévu pour des sélections nécessitant
	 * les deux parents individuellement
	 */
	vector<int> d_parent_2;
	

	/**
	 * @brief Stocke la liste des parents sélectionné a la fin de l'étape de sélection
	 */
	vector<vector<int>> d_parents;

};

