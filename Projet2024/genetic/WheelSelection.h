#pragma once

#include "Selection.h"

class WheelSelection : public Selection
{
	void select(vector<vector<int>>& population, vector<double> score) override;

};

