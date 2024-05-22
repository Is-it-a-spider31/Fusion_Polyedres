#pragma once

#include <vector>
#include <random>
#include <iostream>

using namespace std;

class Selection
{
public:

	virtual void select(vector<vector<int>>& population, vector<double> score) = 0;
	vector<int> getParent1() const;
	int getId_p1() const;
	int getId_p2() const;
	vector<int> getParent2() const;

protected:

	vector<int> d_parent_1;
	vector<int> d_parent_2;
	int d_id_p1, d_id_p2;

};

