#pragma once

#include <vector>

using namespace std;

class Mutation
{

public:
	/**
	 * @brief Mutation d'un individu 
	*/
	virtual void mutate(vector<int>& individual) = 0;

};

