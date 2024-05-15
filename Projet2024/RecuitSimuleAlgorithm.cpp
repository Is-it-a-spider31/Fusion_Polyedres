#include "RecuitSimuleAlgorithm.h"

RecuitSimuleAlgorithm::RecuitSimuleAlgorithm(const string& filename) 
	: Algorithm(filename), 
	d_coolingFactor(0.85), 
	d_temperature(100),
	d_randomGenerator(std::random_device()())
{}

/**
 * @brief Algoritme principal du recuit simule
*/
void RecuitSimuleAlgorithm::run()
{
	// INITIALISATION

	// Copies de la liste des polyedres
	vector<Polyedre> currentSolution = d_polyhedra;
	vector<Polyedre> neighborSolution = d_polyhedra;	// Solution voisine

	this->permute2Elements(currentSolution);
	int currentEval = this->evaluateSolution(currentSolution);
	int neighborEval;
	int n = 0;
	double palier;

	do
	{
		// PERTURBATION
		this->permute2Elements(neighborSolution);

		// EVALUATION
		neighborEval = this->evaluateSolution(neighborSolution);

		// ACCEPTATION
		if (isNeighborAccepted(currentEval, neighborEval))
		{
			currentSolution = neighborSolution;
			currentEval = neighborEval;
		}

		// REFROIDISSEMENT
		d_temperature--;
		palier = std::exp(d_temperature * d_coolingFactor);
		n++;

	} while (n <= palier);	// Critere d'arret (a changer)
}

/**
 * @brief Permute 2 elements dans la liste
 *
 * @param polyhedra Reference vers la liste de polyedres a permuter
*/
void RecuitSimuleAlgorithm::permute2Elements(vector<Polyedre>& polyhedra)
{
	if (!polyhedra.empty())
	{
		// Genere un index aléatoire dans l'interval [0, size()-1]
		// selon une loi de distribution uniforme
		std::uniform_int_distribution<size_t> dis(0, polyhedra.size() - 1);
		size_t index = dis(d_randomGenerator);

		// Permute l'element à l'index avec un autre element choisi aleatoirement
		std::swap(polyhedra[index], polyhedra[dis(d_randomGenerator)]);
	}
}

/**
  * @brief Teste si la solution voisine est acceptee ou pas
  *
  * Calcule la probabilite d'acceptation de la solution voisine
  * avec la formule classique donne dans l'algo du recuit simule.
  *
  * @param currentEval Evaluation de la solution courante
  * @param neighborEval Evaluation de la solution voisine
  *
  * @return true si solution voisine acceptee, false sinon
 */
bool RecuitSimuleAlgorithm::isNeighborAccepted(const int& currentEval, const int& neighborEval)
{
	bool isAccepted = true;

	if (neighborEval > currentEval)
	{	// Acceptation possible avec une certaine probabilite

		double proba = std::exp((currentEval - neighborEval) * d_temperature);

		// Distribution uniforme dans [0, 1]
		std::uniform_real_distribution<double> uniformDis(0.0, 1.0);
		// Genere un nombre entre 0 et 1
		double random = uniformDis(d_randomGenerator);

		if (random >= proba)
			isAccepted = false;
	}

	return isAccepted;
}
