#pragma once

#include "Selection.h"

/**
 * @brief Implementation de la selection par roulette
 */
class WheelSelection : public Selection
{

	/**
 * @brief S�lectionne des individus dans la population en utilisant une s�lection par roulette.
 *
 * Cette m�thode s�lectionne des individus dans la population en utilisant une s�lection par roulette.
 * Les individus sont s�lectionn�s de mani�re al�atoire.
 * Les individus s�lectionn�s sont retir�s de la population d'origine.
 *
 * @param population La population � partir de laquelle s�lectionner.
 * @param score Les scores associ�s � chaque individu de la population.
 */
	void select(vector<vector<int>>& population, vector<double> score) override;

};

