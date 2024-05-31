#include "RecuitSimuleAlgorithm.h"

#include <algorithm>	// Pour std:swap
#include <time.h>

#include "OBJFileHandler.h"
#include "myUtils.h"	// Pour doubleToStringRounded()

/**
 * Chemin du repertoire ves lequel l'agoritme ecrit
 * les solutions trouvees sous forme de fichiers .obj
*/
const string RecuitSimuleAlgorithm::GENERATE_OBJ_PATH = "Tests/generated/RecuitSimule/";


RecuitSimuleAlgorithm::RecuitSimuleAlgorithm(const string& filename)
	: Algorithm(filename),
	d_coolingFactor(0.99),
	d_temperature(3000),
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
	vector<Polyedre> bestSolution = d_polyhedra;
	vector<Polyedre> neighborSolution = d_polyhedra;	// Solution voisine

	double currentEval = this->evaluateSolution(currentSolution);
	double neighborEval;
	double bestEval = currentEval;
	double palier;
	double n = 0;

	int nbIterations = 0;
	int nonImprovIter = 0;
	int nonImprovLimit = 1000;

	// Parametres
	const int maxIter = 14;
	const int initialTemp = d_temperature;
	int nbPermutations = 4;

	// Debut du chronometre (pour compter le temps d'execution)
	clock_t tStart = clock();

	while (d_temperature > 1)	// Critere d'arret (a changer)
	{
		// REFROIDISSEMENT
		d_temperature *= d_coolingFactor;
		palier = std::exp(1 / (d_temperature * d_coolingFactor));

		//cout << "palier : " << palier << endl;
		n = 0;
		d_dataWriter.addPoint(nbIterations, currentEval);	// ADD DATA

		if (nbIterations % 7 == 0) {
			cout << "temperature : " << d_temperature << endl;
		}

		while (n < maxIter)
		{
			nbIterations++;

			//cout << "\tn : " << n << endl;
			// PERTURBATION
			neighborSolution = currentSolution;
			int min = 0.15 * d_polyhedra.size();
			int max = 0.7 * d_polyhedra.size();
			nbPermutations = min + (nonImprovIter / nonImprovLimit) * (max - min);
			this->permuteNElements(neighborSolution, nbPermutations);

			// EVALUATION
			neighborEval = this->evaluateSolution(neighborSolution);
			//cout << "Eval : " << neighborEval << endl;

			if (neighborEval < bestEval)	// Update best solution
			{
				bestSolution = neighborSolution;
				bestEval = neighborEval;
			}

			// ACCEPTATION
			if (isNeighborAccepted(currentEval, neighborEval)
				|| nonImprovIter > nonImprovLimit)
			{
				currentSolution = neighborSolution;
				currentEval = neighborEval;
				nonImprovIter = 0;
			}
			else
			{
				nonImprovIter++;
			}

			n++;
		}
	}

	// Fin du chronometre
	double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;

	// Fusion sur la meilleur solution trouvee
	const vector<Polyedre> mergedSolution = mergeAlgorithm(bestSolution);

	// ECRITURE DE LA MEILLEURE SOLUTION EN OBJ
	cout << "SIZE : " << mergedSolution.size() << endl;
	// Ecriture du fichier OBJ pour cette solution
	string filename = GENERATE_OBJ_PATH + "FUSION."
		+ to_string(mergedSolution.size()) + ".obj";
	OBJFileHandler::writeOBJ(d_vertices, mergedSolution, filename);

	// AFFICHAGE DU GRAPHIQUE

	// Temps d'execution en string
	string strExecutionTime;
	if (timeTaken < 60)
	{
		strExecutionTime = doubleToStringRounded(timeTaken, 3) + " s";
	}
	else 
	{
		int minutes = static_cast<int>(timeTaken) / 60;
		double seconds = timeTaken - (minutes * 60);
		strExecutionTime = to_string(minutes) + " min " + doubleToStringRounded(seconds, 3) + " s";
	}

	// Encadre d'information sur le graphique
	string info = "Nb permutations pour voisin : -not used " + to_string(nbPermutations) + "\\n";
	info += "Initial temp : " + to_string(initialTemp) + "\\n";
	info += "Facteur refroidissement : " + doubleToStringRounded(d_coolingFactor, 3) + "\\n";
	info += "Nb iteration par palier : " + to_string(maxIter) + "\\n";
	info += "Nb iteration effectuees : " + to_string(nbIterations) + "\\n";
	info += "Temps d'execution : " + strExecutionTime + "\\n";
	info += "Best eval : " + to_string(bestEval)+ "\\n";
	info += "Taille finale : " + to_string(mergedSolution.size())+ "\\n";
	info += "Solution : ";
	for (auto& p : bestSolution)	// Affiche la solution
		info += p.getId() + " ";

	cout << info << endl;
	this->printDataChart(info);
}

/**
 * @brief Permute N > 1 elements dans la liste
 *
 * @param polyhedra Liste de polyedres a permuter
 * @param n nombre d'elements a permuter
*/
void RecuitSimuleAlgorithm::permuteNElements(vector<Polyedre>& polyhedra, const size_t n)
{
	// Si liste vide ou n < 2 : permutation impossible
	if (polyhedra.empty() || n < 2 || n > polyhedra.size())
		return;

	std::uniform_int_distribution<size_t> dis(0, polyhedra.size() - 1);
	vector<size_t> indices;	// indices des N elements a permuter

	// Liste des N indices a permuter
	while (indices.size() < n)
	{
		size_t index = dis(d_randomGenerator);	// Indice aleatoire
		// Il faut que l'indice soit different des precedents
		if (std::find(indices.begin(), indices.end(), index) == indices.end())
			indices.push_back(index);	// Ajout de l'indice
	}

	// Ajout des elements a permuter dans une liste temporaire
	vector<Polyedre> temp(n);
	for (size_t i = 0; i < n; ++i)
		temp[i] = polyhedra[indices[i]];
	// Melange des elements
	std::shuffle(temp.begin(), temp.end(), d_randomGenerator);

	// Modification de la liste initiale
	for (size_t i = 0; i < n; ++i)
		polyhedra[indices[i]] = temp[i];
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
bool RecuitSimuleAlgorithm::isNeighborAccepted(const double& currentEval, const double& neighborEval)
{
	bool isAccepted = true;

	if (neighborEval > currentEval)
	{	// Acceptation possible avec une certaine probabilite

		//double proba = std::exp((currentEval - neighborEval) / d_temperature) - 1;
		double proba = 2 - exp((1-((neighborEval - currentEval) / 5)) * (d_temperature / 1000));

		// Distribution uniforme dans [0, 1]
		std::uniform_real_distribution<double> uniformDis(0.0, 1.0);
		// Genere un nombre entre 0 et 1
		double random = uniformDis(d_randomGenerator);
		//cout << "proba" << proba << endl;
		//cout << "random" << random << endl;

		//if (random < proba)
			isAccepted = false;
	}

	return isAccepted;
}

/**
 * @brief Affiche le graphique qui montre l'evolution des donnees de l'algo
 */
void RecuitSimuleAlgorithm::printDataChart(const string& info)
{
	const string legend = "";
	const string title = "Evolution de l'objectif en fonction de la temperature";
	d_dataWriter.writeDataToFile(
		GENERATE_OBJ_PATH+"RecuitChart",	// Nom fichier
		"Nb iteration",	// Axe X
		"Objectif",		// Axe Y
		legend,
		title,
		info,
		true	// Invertion de l'axe X
	);
}