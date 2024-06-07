#pragma once
#include "Selection.h"

/**
 * @brief Implementation de la selection par tournoi
 */
class TurnamentSelection : public Selection
{
public:

	/**
 * @brief Sélectionne des individus dans un sous ensemble de la population à l'aide d'un tournoi.
 *
 * Cette méthode sélectionne des individus dans la population en utilisant un tournoi.
 * Un tournoi est organisé entre les individus du sous ensemble de la population pour sélectionner les gagnants.
 * Les individus sélectionnés sont retirés de la population d'origine.
 *
 * @param population Le sous ensemble à partir duquel sélectionner.
 * @param score Les scores associés à chaque individu du sous ensemble.
 */
	void select(vector<vector<int>>& population, vector<double> score) override;


	/**
 * @brief Effectue un tournoi pour sélectionner un gagnant.
 *
 * Cette méthode organise un tournoi entre un nombre spécifié d'individus de la population.
 * Elle sélectionne le meilleur individu en fonction de leurs scores et l'ajoute aux parents sélectionnés.
 *
 * @param population La population à partir de laquelle sélectionner.
 * @param score Les scores associés à chaque individu de la population.
 * @param winnerInd L'indice du gagnant dans la population.
 */
	void oneWinnerTurnament(vector<vector<int>>& population, vector<double>& score, int& winner);

private:

	/**
	 * @brief Nombre d'individu dans le tournoi
	 */
	int nbIndivInTurnament = 0;


};

