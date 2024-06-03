#include "GeneticAlgorithm.h"
#include <time.h>

/**
 * Chemin du repertoire ves lequel l'agoritme ecrit
 * les solutions trouvees sous forme de fichiers .obj
*/
const string GeneticAlgorithm::GENERATE_OBJ_PATH = "Tests/generated/GeneticAlgo/";

GeneticAlgorithm::GeneticAlgorithm(const string& filename, int popSize, double probaCross, double probaMut, int maxIter, Selection& selection, Crossover& crossover, Mutation& mutation) :
	Algorithm(filename), d_popSize{ popSize }, d_crossoverProba{probaCross}, d_mutationProba{probaMut}, d_maxIteration{maxIter}
{
	d_Selection = &selection;
	d_Crossover = &crossover;
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
	clock_t tStart = clock();
	d_dataWriters.push_back(ExportAlgoData());

		//Initialisation
		d_Population = new Population{ d_dimension, d_popSize };
		d_pop = d_Population->randomInit();

		//Evaluation
		double scoreMin = 10e6;

		d_score_pop.clear();
		for (int i = 0; i < d_popSize; i++)
		{
			//Transforme le tableau d'index en tableau de polyhedre
			vector<Polyedre> solution = perm2Poly(i);

			double current_indiv_score = evaluateSolution(solution);
			d_score_pop.push_back(current_indiv_score);

			//MAJ du score max et index
			if (current_indiv_score < scoreMin)
			{
				//cout << "permutation n°" << i << " : score = " << current_indiv_score << " | NB POLYEDRE FINAL : " << evaluateSolution(solution) << endl;
				scoreMin = current_indiv_score;
				d_permutScoreMax = solution;
			}

		}

		d_oldpop = d_pop;
		d_oldscore_pop = d_score_pop;

		//printPopulation();
		
		cout << "=====================================================================" << endl;
		cout << "Meilleur score apres init : " << scoreMin << " | [ ";
		for (const auto& i : d_permutScoreMax)
		{
			std::cout << i.getId() << " ";
		}
		cout << endl;
		cout <<"=====================================================================" << endl;


		//SI d_popsize = tgamma(d_dimension + 1) BREAK pck on a déja fait toutes les permutations
		// donc il faut renvoyer le meilleur score. 
		//if(d_popresized) { break; }
		if(d_popResized)
		{
			vector<Polyedre> solution_merged = mergeAlgorithm(d_permutScoreMax);

			//Ecriture de la solution puis fin de la boucle
			string filename = GENERATE_OBJ_PATH + "FUSION." + to_string(solution_merged.size()) + ".obj";
			OBJFileHandler::writeOBJ(d_vertices, solution_merged, filename);

			return;
		}

		else
		{
			//-----------------------------TANT QUE----------------------------------------------------
			int iteration = 0;
			//while (iteration < d_maxIteration)
			//double stop = 20;

			while(iteration < d_maxIteration)
			{
				d_dataWriters[0].addPoint(iteration, scoreMin);

				cout << "------ITERATION " << iteration << " --------" << endl;
				//printPopulation();
				if(iteration % 10 == 0) printPopulation();
				cout << "----------------" << endl;
				
				//Selection
				d_Selection->select(d_oldpop, d_oldscore_pop);


				//SUPPRIMER LES TRUCS EN TROP DE LA POPULATION NORMALE
				d_pop.clear();

						vector<int> child1, child2;
						for (int i = 0; i < d_Selection->getParents().size() - 1; i=i+2)
						{

							child1.clear();
							child2.clear();

							vector<int> tmpP1, tmpP2;
							tmpP1 = d_Selection->getParents()[i];
							tmpP2 = d_Selection->getParents()[i+1];
							
							d_Crossover->cross(d_Selection->getParents()[i], d_Selection->getParents()[i + 1], child1, child2);

							int rdm_mut = rand() % 101;
							if (rdm_mut < d_mutationProba * 100)
							{
								d_Mutation->mutate(child1);

							}

							rdm_mut = rand() % 101;
							if (rdm_mut < d_mutationProba * 100)
							{
								d_Mutation->mutate(child2);

							}

							d_pop.push_back(child1);
							d_pop.push_back(child2);
						}

						while (d_pop.size() < d_popSize)
						{
							//remplir le reste random
							vector<int> individual(d_dimension);
							for (int i = 0; i < d_dimension; ++i) {
								individual[i] = i;
							}
							random_shuffle(individual.begin(), individual.end());

							d_pop.push_back(individual);
						}
						
						

					//}

					//Création de propba mutation
					

					//Evaluer l'indiv modifier et modifier si besoin le scoreMax
						for (int indice = 0; indice < d_pop.size(); indice++)
						{
							vector<Polyedre> toEvaluate = perm2Poly(indice);
							double new_indiv_score = evaluateSolution(toEvaluate);
							d_score_pop[indice] = new_indiv_score;

							if (new_indiv_score < scoreMin)
							{
								scoreMin = new_indiv_score;
								d_permutScoreMax = toEvaluate;
							}
							
							//cout << "indice : " << indice << "  ------- popsize : " << d_pop.size() << endl;
						}
					

				cout << "Best score : " << scoreMin << endl;
				cout << "Best indiv : [ ";
				for (const auto& i : d_permutScoreMax)
				{
					cout << i.getId() << " ";
				}
				cout << " ]" << endl;

				//cout << "------------ITERATION " << iteration << "---------------" << endl;
				iteration++;
				d_oldpop = d_pop;
				d_oldscore_pop = d_score_pop;

				d_Selection->clearParentsList();
			}

			vector<Polyedre> solution_merged = mergeAlgorithm(d_permutScoreMax);
			string filename = GENERATE_OBJ_PATH + "FUSION." + to_string(solution_merged.size()) + ".obj";
			OBJFileHandler::writeOBJ(d_vertices, solution_merged, filename);

			double timetaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;

			// AFFICHAGE DU GRAPHIQUE
			string info = "Nb itérations : " + to_string(iteration) + "\\n";
			info += "Best eval : " + to_string(scoreMin) + "\\n";
			info += "Solution : ";
			for (auto& p : d_permutScoreMax)	// Affiche la solution
				info += p.getId() + " ";
			info += "\\n";
			info += "Taille finale : " + to_string(solution_merged.size()) + "\\n";

			if (timetaken < 60) {
				info += "Temps execution : " + to_string(timetaken) + " s\\n";
			}
			else {
				int minutes = static_cast<int>(timetaken) / 60;
				double seconds = timetaken - (minutes * 60);
				info += "Temps execution : " + to_string(minutes) + " min " + to_string(seconds) + " s\\n";
			}

			cout << info << endl;
			this->printDataChart(info);
			
			
		}
	

}

void GeneticAlgorithm::printPopulation() const
{
	for (int i = 0; i < d_pop.size(); i++)
	{
		cout << "[ ";
		for (int j = 0; j < d_dimension; j++)
		{
			cout << d_pop[i][j] << " ";
		}
		cout << "] ---- n"<< i << endl;
	}
}

void GeneticAlgorithm::exportBest()
{
	vector<Polyedre> solution_merged = mergeAlgorithm(d_permutScoreMax);
	string filename = GENERATE_OBJ_PATH + "FUSION." + to_string(solution_merged.size()) + ".obj";
	OBJFileHandler::writeOBJ(d_vertices, solution_merged, filename);

}

void GeneticAlgorithm::printDataChart(const string& info)
{
	const string legend = "";
	const string title = "Evolution de l'objectif en fonction des itérations";
	d_dataWriters[0].writeDataToFile(
		GENERATE_OBJ_PATH + "GeneticChart",	// Nom fichier
		"Iteration",	// Axe X
		"Objectif",		// Axe Y
		legend,
		title,
		info,
		false //true	// Invertion de l'axe X
	);
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


