#include "WheelSelection.h"
#include <random>

void WheelSelection::select(vector<vector<int>>& population, vector<double> score)
{
	//Divise la population en 2
	int index_lasthalf = population.size() / 2;

	//garde un tableau pair
	if (index_lasthalf % 2 != 0)
	{
		index_lasthalf--;
	}

	vector<vector<int>> population_no_double = population;
	vector<double> score_no_double = score;

	random_device dev;
	mt19937 rng(dev());


	for (int i = 0; i < index_lasthalf; i++)
	{	
		//selectionne au hasard un individu a ajouter dans les parents
		uniform_int_distribution<std::mt19937::result_type> dist6(0, population_no_double.size() - 1); // distribution in range [1, 6]
		int number = dist6(rng);
		//int number = rand() % population_no_double.size();

		//ajout
		d_parents.push_back(population_no_double[number]);

		//retire le selectionné de la pop
		population_no_double.erase(population_no_double.begin() + number);
		score_no_double.erase(score_no_double.begin() + number);

	}
}
