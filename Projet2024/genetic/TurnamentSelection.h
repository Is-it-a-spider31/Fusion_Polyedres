#pragma once
#include "Selection.h"

class TurnamentSelection : public Selection
{
public:

	void select(vector<vector<int>>& population, vector<double> score) override;

private:

	int nbIndivInTurnament = 0;


};

