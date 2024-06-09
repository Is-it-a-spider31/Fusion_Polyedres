#pragma once
#include "Selection.h"


/**
 * @brief Implementation de la selection elitiste
 */
class BestScoreSelection : public Selection
{
public:
	/**
	 * @brief Les N meilleurs individus sont selectionner en tant que parents
	 * @param population Sélection parmis cette population
	 * @param score Score de la population 
	 */
	void select(vector<vector<int>>& population, vector<double> score) override;
private:

};

