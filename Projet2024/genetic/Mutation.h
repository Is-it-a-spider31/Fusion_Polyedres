#pragma once

#include <vector>

using namespace std;

/**
 * @brief Classe abstraite contenant la fonction mutate a redefinir
 */
class Mutation
{

public:
	/**
	 * @brief Mutation d'un individu 
	*/
	virtual void mutate(vector<int>& individual) = 0;

};

