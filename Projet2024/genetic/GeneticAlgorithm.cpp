#include "GeneticAlgorithm.h"

/**
 * Chemin du repertoire ves lequel l'agoritme ecrit
 * les solutions trouvees sous forme de fichiers .obj
*/
const string GeneticAlgorithm::GENERATE_OBJ_PATH = "Tests/generated/GeneticAlgo/";

GeneticAlgorithm::GeneticAlgorithm(const string& filename, int popSize, double probaCross, double probaMut, int maxIter, Selection& selection, Mutation& mutation) :
	Algorithm(filename), d_popSize{ popSize }, d_crossoverProba{probaCross}, d_mutationProba{probaMut}, d_maxIteration{maxIter}
{
	d_Selection = &selection;
	d_Mutation = &mutation;

	d_dimension = d_polyhedra.size();

	if (d_popSize > tgamma(d_dimension + 1))
	{
		cerr << "Taille de la population > aux nombres de permutations possibles (n!), resize!" << endl;
		d_popSize = tgamma(d_dimension + 1);
		d_popResized = true;
	}
}

void GeneticAlgorithm::run()
{
	//Initialisation
	d_Population = new Population{d_dimension, d_popSize};
	d_pop = d_Population->randomInit();

	printPopulation();

	//Evaluation

	double scoreMax = 0.0;
	
	d_score_pop.clear();
	for (int i = 0; i < d_popSize; i++)
	{
		//Transforme le tableau d'index en tableau de polyhedre
		vector<Polyedre> solution = perm2Poly(i);

		double current_indiv_score = (double)d_dimension / (double)evaluateSolution(solution);
		d_score_pop.push_back(current_indiv_score);

		//MAJ du score max et index
		if (current_indiv_score > scoreMax)
		{
			//cout << "permutation n°" << i << " : score = " << current_indiv_score << " | NB POLYEDRE FINAL : " << evaluateSolution(solution) << endl;

			scoreMax = current_indiv_score;
			d_permutScoreMax = solution;
		}

	}

	//SI d_popsize = tgamma(d_dimension + 1) BREAK pck on a déja fait toutes les permutations
	// donc il faut renvoyer le meilleur score. 
	//if(d_popresized) { break; }
	if (d_popResized)
	{
		vector<Polyedre> solution_merged = mergeAlgorithm(d_permutScoreMax);

		//Ecriture de la solution puis fin de la boucle
		string filename = GENERATE_OBJ_PATH+"FUSION."+ to_string(solution_merged.size()) + ".obj";
		OBJFileHandler::writeOBJ(d_vertices, solution_merged, filename);

		return ;
	}

	else 
	{
	//-----------------------------TANT QUE----------------------------------------------------
		int iteration = 0;
		while (iteration < d_maxIteration)
		{

			for (int individu = 0; individu < d_popSize; individu++)
			{
				//Selection
				d_Selection->select(d_pop, d_score_pop);

				//Création de proba croisement
				int rdm_cross = rand() % 101;
				if (rdm_cross < d_crossoverProba * 100)
				{
					//CROISEMENT
				}

				//Création de propba mutation
				int rdm_mut = rand() % 101;
				if (rdm_mut < d_mutationProba * 100)
				{
					d_Mutation->mutate(d_pop[individu]);
				}

				//Evaluer l'indiv modifier et modifier si besoin le scoreMax

				vector<Polyedre> toEvaluate = perm2Poly(individu);
				double new_indiv_score = (double)d_dimension / (double)evaluateSolution(toEvaluate);

				if (new_indiv_score > scoreMax)
				{
					scoreMax = new_indiv_score;
					d_permutScoreMax = toEvaluate;
				}

			}

			cout << "Best score : " << scoreMax << endl;
			cout << "Best indiv : [ ";
			for (const auto& i : d_permutScoreMax)
			{
				cout << i.getId() << " ";
			}
			cout << " ]" << endl;

			cout << "------------ITERATION " << iteration << "---------------" << endl;
			iteration++;
		}

		vector<Polyedre> solution_merged = mergeAlgorithm(d_permutScoreMax);
		string filename = GENERATE_OBJ_PATH + "FUSION." + to_string(solution_merged.size()) + ".obj";
		OBJFileHandler::writeOBJ(d_vertices, solution_merged, filename);
	}



	
	

}

void GeneticAlgorithm::printPopulation() const
{
	for (const auto& i : d_pop)
	{
		cout << "[ ";
		for (const auto& e : i)
		{
			cout << e << " ";
		}
		cout << "]" << endl;
	}
}

vector<Polyedre> GeneticAlgorithm::perm2Poly(int index)
{
	vector<Polyedre> solution;
	for (int j = 0; j < d_dimension; j++)
	{
		solution.push_back(d_polyhedra[d_pop[index][j]]);
	}
	return solution;
}


