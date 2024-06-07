#pragma once

#include "Selection.h"

/**
 * @brief Implementation de la selection par roulette
 */
class WheelSelection : public Selection
{

	/**
 * @brief Sélectionne des individus dans la population en utilisant une sélection par roulette.
 *
 * Cette méthode sélectionne des individus dans la population en utilisant une sélection par roulette.
 * Les individus sont sélectionnés de manière aléatoire.
 * Les individus sélectionnés sont retirés de la population d'origine.
 *
 * @param population La population à partir de laquelle sélectionner.
 * @param score Les scores associés à chaque individu de la population.
 */
	void select(vector<vector<int>>& population, vector<double> score) override;

};

