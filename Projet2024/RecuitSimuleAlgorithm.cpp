#include "RecuitSimuleAlgorithm.h"

#include <algorithm>	// Pour std:swap
#include "OBJFileHandler.h"

/**
 * Chemin du repertoire ves lequel l'agoritme ecrit
 * les solutions trouvees sous forme de fichiers .obj
*/
const string RecuitSimuleAlgorithm::GENERATE_OBJ_PATH = "Tests/generated/RecuitSimule/";


RecuitSimuleAlgorithm::RecuitSimuleAlgorithm(const string& filename) 
	: Algorithm(filename), 
	d_coolingFactor(0.99), 
	d_temperature(10000),
	d_randomGenerator(std::random_device()())
{

}

/**
 * @brief Algorithme principal du recuit simule
*/
void RecuitSimuleAlgorithm::run()
{
	// INITIALISATION

	// Copies de la liste des polyedres
	vector<Polyedre> currentSolution = d_polyhedra;
	vector<Polyedre> neighborSolution = d_polyhedra;	// Solution voisine

	int currentEval = this->evaluateSolution(currentSolution);
	int neighborEval;
	double palier;
	double n = 0;

	while (d_temperature > 1)	// Critere d'arret (a changer)
	{
		// REFROIDISSEMENT
		d_temperature *= d_coolingFactor;
		palier = std::exp(1 / (d_temperature * d_coolingFactor));

		//cout << "temperature : " << d_temperature << endl;
		//cout << "palier : " << palier << endl;
		n = 0;

		while (n < palier)
		{
			//cout << "\tn : " << n << endl;
			// PERTURBATION
			neighborSolution = currentSolution;
			this->permute2Elements(neighborSolution);

			// EVALUATION
			neighborEval = this->evaluateSolution(neighborSolution);

			// ACCEPTATION
			if (isNeighborAccepted(currentEval, neighborEval))
			{
				currentSolution = neighborSolution;
				currentEval = neighborEval;
			}
			n+=0.15;
		} 
	}

	// ECRITURE

	cout << "SIZE : " << currentSolution.size() << endl;
	// Ecriture du fichier OBJ pour cette solution
	string filename = GENERATE_OBJ_PATH  + "FUSION." 
		+ to_string(currentSolution.size()) + ".obj";
	OBJFileHandler::writeOBJ(d_vertices, currentSolution, filename);
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

		size_t index2 = dis(d_randomGenerator);
		while (index2 == index)
			index2 = dis(d_randomGenerator);

		// Permute l'element à l'index avec un autre element choisi aleatoirement
		std::swap(polyhedra[index], polyhedra[index2]);
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

		double proba = std::exp((currentEval - neighborEval) / d_temperature);

		// Distribution uniforme dans [0, 1]
		std::uniform_real_distribution<double> uniformDis(0.0, 1.0);
		// Genere un nombre entre 0 et 1
		double random = uniformDis(d_randomGenerator);
		//cout << "proba" << proba << endl;
		//cout << "random" << random << endl;

		if (random >= proba)
			isAccepted = false;
	}

	return isAccepted;
}
