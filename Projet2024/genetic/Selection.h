#pragma once

#include <vector>
#include <random>
#include <iostream>

using namespace std;

class Selection
{
public:

	virtual void select(vector<vector<int>>& population, vector<double> score) = 0;

protected:

	vector<int> d_parent_1;
	vector<int> d_parent_2;

};

