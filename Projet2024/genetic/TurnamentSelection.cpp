#include "TurnamentSelection.h"

void TurnamentSelection::select(vector<vector<int>>& population, vector<double> score)
{
	//nbIndivInTurnament = population.size() / 8;

	//divise la population en 2 et fait en sorte d'avoir un tableau pair
	int index_lasthalf = population.size() / 2;
	if (index_lasthalf % 2 != 0)
	{
		index_lasthalf--;
	}

	vector<vector<int>> population_no_double = population;
	vector<double> score_no_double = score;

	//tant qu'il y'a de la place dans le tableau parents on fait un tournoi avec un gagnant
	for (int i = 0; i < index_lasthalf; i++)
	{
		int winnerInd;
		//cout << "parents size " << d_parents.size() << endl;
		oneWinnerTurnament(population_no_double, score, winnerInd);
		//retire le winner de la pop et du score

		population_no_double.erase(population_no_double.begin() + winnerInd);
		score_no_double.erase(score_no_double.begin() + winnerInd);

	}

	/*for (const auto& t : d_parents)
	{
		cout << "[ ";
		for (const auto& j : t)
		{
			cout << j << " ";
		}
		cout << " ]" << endl;;
	}*/

	//---------------------------------------------

	
	
}

void TurnamentSelection::oneWinnerTurnament(vector<vector<int>>& population, vector<double>& score, int& winnerInd)
{
	nbIndivInTurnament = population.size() / 4;

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

	int winner1 = indexToFight[0];
	for (const auto& indiv : indexToFight)
	{
		if (score[indiv] < score[winner1])
		{
			winner1 = indiv;
		}
	}

	//cout << "Winner 1 = " << winner1 << " | Winner 2 = " << winner2 << endl;
	d_parents.push_back(population[winner1]);
	winnerInd = winner1;
}
