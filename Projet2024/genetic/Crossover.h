#pragma once

#include <vector>

using namespace std;

class Crossover
{

public:

	virtual void cross(
		const vector<int>& parent1, 
		const vector<int>& parent2,
		vector<int>& child1,
		vector<int>& child2
	) = 0;
};

