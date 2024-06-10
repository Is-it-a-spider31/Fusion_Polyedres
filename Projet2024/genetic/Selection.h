#pragma once

#include <vector>
#include <random>
#include <iostream>

using namespace std;

/**
 * @brief Classe de s�lection abstraite contenant la m�thode select a redefinir ainsi que la liste des parents
 */

class Selection
{
public:

	/**
 * @brief S�lectionne des individus dans la population.
 *
 *  S�lectionne des individus de la population et doit remplir la liste de parents d_parents
 *
 * @param population La population � partir de laquelle s�lectionner.
 * @param score Les scores associ�s � chaque individu de la population.
 */
	virtual void select(vector<vector<int>>& population, vector<double> score) = 0;
	
	/**
	 * @brief R�cup�re le premier parent individuel
	 * @return Le premier parent
	 */
	vector<int> getParent1() const;

	/**
	 * @brief R�cup�re le deuxi�me parent individuel
	 * @return Le premier parent
	 */
	vector<int> getParent2() const;

	/**
	 * @brief R�cupere la liste des parents 
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
	 * N'est pas utilis�, mais �st pr�vu pour des s�lections n�cessitant 
	 * les deux parents individuellement
	 */

	vector<int> d_parent_1;

	/**
	 * @brief Stocke le deuxi�me parent
	 * N'est pas utilis�, mais �st pr�vu pour des s�lections n�cessitant
	 * les deux parents individuellement
	 */
	vector<int> d_parent_2;
	

	/**
	 * @brief Stocke la liste des parents s�lectionn� a la fin de l'�tape de s�lection
	 */
	vector<vector<int>> d_parents;

};

