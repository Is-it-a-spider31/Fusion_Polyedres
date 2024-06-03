#include "BestScoreSelection.h"

void BestScoreSelection::select(vector<vector<int>>& population, vector<double> score)
{
	vector<int> indexes(population.size());
	for (int i = 0; i < indexes.size(); i++)
	{
		indexes[i] = i;
	}

	sort(indexes.begin(), indexes.end(),[&score](size_t a, size_t b) 
		{
		 return score[a] < score[b];
		});

	vector<std::vector<int>> sorted_population(population.size());
	vector<double> sorted_scores(score.size());

	for (size_t i = 0; i < indexes.size(); ++i) {
		sorted_population[i] = population[indexes[i]];
		sorted_scores[i] = score[indexes[i]];
	}

	// Copier les résultats triés dans les vecteurs originaux
	population = sorted_population;
	score = sorted_scores;

	int index_lasthalf = population.size() / 2;
	if (index_lasthalf % 2 != 0)
	{
		index_lasthalf--;
	}

	for (int i = 0; i < index_lasthalf; i++)
	{
		d_parents.push_back(population[i]);
	}


	/*for (int i = 0; i < population.size(); i++)
	{
		cout << "[ ";
		for (int j = 0; j < population[i].size(); j++)
		{
			cout << population[i][j] << " ";
		}
		cout << "] ---- n" << i  << " ---- score : " << score[i] << endl;
	}*/




}