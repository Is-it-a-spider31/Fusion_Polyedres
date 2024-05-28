#pragma once
#include "Selection.h"

class BestScoreSelection : public Selection
{
public:

	void select(vector<vector<int>>& population, vector<double> score) override;
private:

};

