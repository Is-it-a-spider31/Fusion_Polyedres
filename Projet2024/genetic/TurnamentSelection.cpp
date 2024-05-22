#include "TurnamentSelection.h"

void TurnamentSelection::select(vector<vector<int>>& population, vector<double> score)
{
	//nbIndivInTurnament = population.size() / 8;
	nbIndivInTurnament = 2;

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

	/*cout << "Index in turnament : [ ";
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
	cout << " ]" << endl;*/

	int winner1 = indexToFight[0];
	for (const auto& indiv : indexToFight)
	{
		if (score[indiv] > score[winner1])
		{
			winner1 = indiv;
		}
	}

	//cout << "Winner 1 = " << winner1 << " | Winner 2 = " << winner2 << endl;
	d_parent_1 = population[winner1];
	d_id_p1 = winner1;
	cpt_correct_number = 0;

	vector<int> indexToFight2(nbIndivInTurnament, -1);
	while (cpt_correct_number < nbIndivInTurnament)
	{
		int number = rand() % population.size();
		while (number == winner1)
		{
			number = rand() % population.size();
		}

		if (find(indexToFight2.begin(), indexToFight2.end(), number) == indexToFight2.end())
		{
			indexToFight2[cpt_correct_number] = number;
			cpt_correct_number++;
		}
	}

	int winner2 = indexToFight2[0];
	for (const auto& indiv : indexToFight2)
	{
		if (score[indiv] > score[winner2])
		{
			winner2 = indiv;
		}
	}

	d_parent_2 = population[winner2];
	d_id_p2 = winner2;
	
}