#include "WheelSelection.h"


void WheelSelection::select(vector<vector<int>>& population, vector<double> score)
{
	int index_lasthalf = population.size() / 2;
	if (index_lasthalf % 2 != 0)
	{
		index_lasthalf--;
	}

	vector<vector<int>> population_no_double = population;
	vector<double> score_no_double = score;

	for (int i = 0; i < index_lasthalf; i++)
	{
		cout << " pop no double size : " << population_no_double.size() << endl;
		int number = rand() % population_no_double.size();
		d_parents.push_back(population_no_double[number]);

		//retire le selectionné de la pop
		population_no_double.erase(population_no_double.begin() + number);
		score_no_double.erase(score_no_double.begin() + number);

		cout << "parent tiré : " << number << endl;
		cout << "[ ";
		for (int j = 0; j < d_parents[i].size(); j++)
		{
			cout << d_parents[i][j] << " ";
		}
		cout << endl;
	}
}
