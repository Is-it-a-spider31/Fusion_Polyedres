#include "TurnamentSelection.h"

void TurnamentSelection::select(vector<vector<int>>& population, vector<double> score)
{
	//nbIndivInTurnament = population.size() / 8;
	nbIndivInTurnament = 6;

	vector<int> indexToFight(nbIndivInTurnament, -1);

	int cpt_correct_number = 0;
	while (cpt_correct_number < nbIndivInTurnament)
	{
		int number = rand() % population.size();
		if (find(indexToFight.begin(), indexToFight.end(), number) == indexToFight.end())
		{
			indexToFight[cpt_correct_number] = number;
			cpt_correct_number++;
		}
	}

	cout << "Index in turnament : [ ";
	for (const auto& ind : indexToFight)
	{
		cout << ind << " ";
	}
	cout << " ]" << endl;

	cout << "Score of them : [ ";
	for (const auto& ind : indexToFight)
	{
		cout << score[ind] << " ";
	}
	cout << " ]" << endl;

	int winner1 = indexToFight[0];
	int winner2 = indexToFight[0];

	for (const auto& indiv : indexToFight)
	{
		if (score[indiv] > score[winner2])
		{
			if (score[indiv] > score[winner1])
			{
				winner1 = indiv;
			}
			else
			{
				winner2 = indiv;
			}
		}
	}

	cout << "Winner 1 = " << winner1 << " | Winner 2 = " << winner2 << endl;
	
	d_parent_1 = population[winner1];
	d_parent_2 = population[winner2];

	
}