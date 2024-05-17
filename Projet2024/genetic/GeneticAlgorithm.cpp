#include "GeneticAlgorithm.h"

/**
 * Chemin du repertoire ves lequel l'agoritme ecrit
 * les solutions trouvees sous forme de fichiers .obj
*/
const string GeneticAlgorithm::GENERATE_OBJ_PATH = "Tests/generated/GeneticAlgo/";

GeneticAlgorithm::GeneticAlgorithm(const string& filename, int popSize, double probaCross, double probaMut, int maxIter) :
	Algorithm(filename), d_popSize{ popSize }, d_crossoverProba{probaCross}, d_mutationProba{probaMut}
{
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
	population = new Population{d_dimension, d_popSize};
	d_pop = population->randomInit();

	printPopulation();

	//Evaluation
	double scoreMax = 0.0;
	int index_scoreMax = -1;

	//-----------------------------TANT QUE----------------------------------------------------

	for (int i = 0; i < d_popSize; i++)
	{
		//Transforme le tableau d'index en tableau de polyhedre
		vector<Polyedre> solution;
		for (int j = 0; j < d_dimension; j++)
		{
			solution.push_back(d_polyhedra[d_pop[i][j]]);
		}

		double current_indiv_score = (double)d_dimension / (double)evaluateSolution(solution);


		//MAJ du score max et index
		if (current_indiv_score > scoreMax)
		{
			cout << "permutation n°" << i << " : score = " << current_indiv_score << " | NB POLYEDRE FINAL : " << evaluateSolution(solution) << endl;

			scoreMax = current_indiv_score;
			index_scoreMax = i;
		}

	}

	//SI d_popsize = tgamma(d_dimension + 1) BREAK pck on a déja fait toutes les permutations
	// donc il faut renvoyer le meilleur score. 
	//if(d_popresized) { break; }
	if (d_popResized)
	{
		vector<Polyedre> solution;
		for (int gene = 0; gene < d_dimension; gene++)
		{
			if (index_scoreMax == -1)
			{
				cerr << "ERREUR" << endl;
				break;
			}

			solution.push_back(d_polyhedra[d_pop[index_scoreMax][gene]]);
		}

		vector<Polyedre> solution_merged = mergeAlgorithm(solution);

		//Ecriture de la solution puis fin de la boucle
		string filename = GENERATE_OBJ_PATH+"FUSION."+ to_string(solution_merged.size()) + ".obj";
		OBJFileHandler::writeOBJ(d_vertices, solution_merged, filename);

		return ;
	}

	
	//Selection

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
