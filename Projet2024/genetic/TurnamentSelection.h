#pragma once
#include "Selection.h"

/**
 * @brief Implementation de la selection par tournoi
 */
class TurnamentSelection : public Selection
{
public:

	/**
 * @brief S�lectionne des individus dans un sous ensemble de la population � l'aide d'un tournoi.
 *
 * Cette m�thode s�lectionne des individus dans la population en utilisant un tournoi.
 * Un tournoi est organis� entre les individus du sous ensemble de la population pour s�lectionner les gagnants.
 * Les individus s�lectionn�s sont retir�s de la population d'origine.
 *
 * @param population Le sous ensemble � partir duquel s�lectionner.
 * @param score Les scores associ�s � chaque individu du sous ensemble.
 */
	void select(vector<vector<int>>& population, vector<double> score) override;


	/**
 * @brief Effectue un tournoi pour s�lectionner un gagnant.
 *
 * Cette m�thode organise un tournoi entre un nombre sp�cifi� d'individus de la population.
 * Elle s�lectionne le meilleur individu en fonction de leurs scores et l'ajoute aux parents s�lectionn�s.
 *
 * @param population La population � partir de laquelle s�lectionner.
 * @param score Les scores associ�s � chaque individu de la population.
 * @param winnerInd L'indice du gagnant dans la population.
 */
	void oneWinnerTurnament(vector<vector<int>>& population, vector<double>& score, int& winner);

private:

	/**
	 * @brief Nombre d'individu dans le tournoi
	 */
	int nbIndivInTurnament = 0;


};

