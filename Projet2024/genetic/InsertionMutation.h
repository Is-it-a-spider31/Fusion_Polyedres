#pragma once

#include <vector>
#include "Mutation.h"

using namespace std;

/**
 * @brief Mutation par insertion
*/
class InsertionMutation : public Mutation
{

	/**
	 * @brief Mutation d'un individu par insertion
	 * @param individual Individu dont un gene doit muter
	*/
	void mutate(vector<int>& individual) override;
};

