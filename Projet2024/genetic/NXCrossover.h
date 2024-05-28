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
	 * Effectue le croisement des 2 parent et modifie
	 * les enfants en parametres en consequence
	 * 
	 * @param[in] parent1 
	 * @param[in] parent2 
	 * @param[out] child1 Enfant vide qui sera modifie
	 * @param[out] child2 Enfant vide qui sera modifie
	*/
	void cross(
		const vector<int>& parent1, 
		const vector<int>& parent2,
		vector<int>& child1,
		vector<int>& child2
	) override;

	/**
	 * @brief Permet de tester le fonctionnement de la classe
	*/
	void test();

private:

	/**
	 * @brief Nombre de points de croisement
	*/
	int d_nbCrossoverPoints;

	/**
	 * @brief Selection aleatoire des points de croisement
	 *
	 * Le nombre de points de croisements depend
	 * de l'attribut @ref NXCrossover::d_nbCrossoverPoints d_nbCrossoverPoints.
	 * Ils sont dans l'interval [1, size-1]
	 *
	 * @param size Taille d'un individu
	 * @return La liste des points de croisements slectionnes
	*/
	vector<int> chooseCrossoverPoints(const int& size);

	/**
	 * @brief Calcul un enfant en croisant 2 parents (croisement N points)
	 *
	 * Attention, l'ordre des parents en parametres a son importance.
	 *
	 * @param parent1 Parent de reference pour le calcul du croisement
	 * @param parent2 Parent qui va servir a modifier les genes de l'enfant
	 * @param child Enfant dont les genes de base sont ceux du parent1
	 * @param crossoverPoints Liste des points de croisement
	*/
	void crossOneChild(
		const vector<int>& parent1,
		const vector<int>& parent2,
		vector<int>& child,
		vector<int> crossoverPoints
	);
};

