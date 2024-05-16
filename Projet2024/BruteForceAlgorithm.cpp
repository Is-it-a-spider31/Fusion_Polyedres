#include "BruteForceAlgorithm.h"


#include "Algorithm.h"

#include <iostream>

#include <fstream>
#include <algorithm>
#include "OBJFileHandler.h"


/**
 * @brief Contructeur a partir d'un fichier .obj
 *
 * @param filename Nom du fichier .obj
*/
BruteForceAlgorithm::BruteForceAlgorithm(const string& filename) 
	: Algorithm(filename) {}

/**
 * @brief Algoritme Brute-force
*/
void BruteForceAlgorithm::run()
{
	// Liste des solutions uniques trouvees
	//	(une solution = ensemble de polyedres)
	vector<vector<Polyedre>> solutions;
	// Nombre de permutations pour chaques solutions
	vector<int> permutationsId;

	// Liste des polyedres permutes
	vector<Polyedre> permutedPolyhedra;

	// Copie de la liste des polyedres dans celle qui sera permutee
	for (int i = 0; i < d_polyhedra.size(); i++)
	{
		permutedPolyhedra.push_back(d_polyhedra[i]);
	}

	// Liste des polyedres avec fusion
	vector<Polyedre> mergedPolyhedra;

	// Solution avec le nombre minimum de polyedres
	int minNbPolySolution = permutedPolyhedra.size();

	// Statistiques
	int nbPermutaions = 0;		// nombre de permuations effectuees
	int nbFullSolutions = 0;	// nombre de solutions qui ont ete calculees jusqu'au bout
	int nbOptimalSolutions = 0;	// nombre de solutions uniques trouvees

	// Pour chaque combinaison de permutation
	//	(complexite n! pour n polyedres)
	do
	{
		// Algoritme de fusion de la solution courante (permutedPolyhedra)
		mergedPolyhedra = mergeAlgorithm(permutedPolyhedra, minNbPolySolution);

		if (!mergedPolyhedra.empty())	// Solution calculee jusqu'au bout
		{
			// Nouveau nombre minimum de polyedre (<= au minimum precedent)
			minNbPolySolution = mergedPolyhedra.size();
			nbFullSolutions++;

			// Vrai si les meme fusions ont deja ete trouvees et ecrites dans un fichier obj
			bool isAlreadyFinded = BruteForceAlgorithm::isSolutionAlreadyFinded(mergedPolyhedra, solutions);

			if (!isAlreadyFinded)	// Si c'est une nouvelle solution
			{
				solutions.push_back(mergedPolyhedra);
				permutationsId.push_back(nbPermutaions);
			}
		}

		// permutedPolyhedrons.clear(); // 1 seul itération si non commente (pour tester)
		mergedPolyhedra.clear();
		nbPermutaions++;

	} while (next_permutation(permutedPolyhedra.begin(), permutedPolyhedra.end()));

	//	ECRITURE DES MEILLEURES SOLUTIONS TROUVEES
	auto solutionId = permutationsId.begin();
	for (vector<Polyedre>& solution : solutions)
	{
		if (solution.size() == minNbPolySolution)
		{
			nbOptimalSolutions++;

			// Ecriture du fichier OBJ pour cette solution
			string filename = "MergeTest/generated/FUSION." + to_string(solution.size())
				+ "Poly_" + to_string(*solutionId) + ".obj";
			OBJFileHandler::writeOBJ(d_vertices, solution, filename);
		}
		++solutionId;
	}

	// Affichage des statistiques
	cout << " ---  STATISTIQUES  ---" << endl;
	cout << "Nb permutations effectuees : " << nbPermutaions << endl;
	cout << "Nb solutions calculees entierement : " << nbFullSolutions << endl;
	cout << "Nb solutions uniques calculees entierement: " << solutions.size() << endl;
	cout << "Nb de solution optimales : " << nbOptimalSolutions << endl;
	cout << "Nb optimale de poledres : " << minNbPolySolution << endl;
}


/**
 * @brief Verifie si une solution de l'algo de fusion a deja ete trouvee
 *
 * Si la solution (ensemble de polyedres) courante est dans
 * la liste des solutions, cela signifie que cette solution a deja
 * ete calculee et trouvee par l'algo de fusion.
 *
 * @param polyhedrons Solution courante de l'algo de fusion
 * @param solutions Liste des solutions deja trouvees
 *
 * @return true Si la solution est presente dans la liste
*/
bool BruteForceAlgorithm::isSolutionAlreadyFinded(
	const vector<Polyedre>& newSolution,		// Nouvelle solution
	const vector<vector<Polyedre>>& solutions	// Liste des solutions trouvees
)
{
	bool isSameSolution = false;	// true si la nouvelle solution est deja dans la liste

	// Parcours des solutions trouvees
	for (vector<Polyedre> solution : solutions)
	{
		// Si la nouvelle solution n'a pas le meme nombre de polyedres
		//	que la solution courante 
		if (solution.size() == newSolution.size())
			isSameSolution = true;

		// Parcours des polyedres d'une solution trouvee (si meme nombre de polyedres)
		int indexSolution = 0;
		while (indexSolution < solution.size() && isSameSolution)
		{
			// Cherche si le polyedre d'une solution est dans la nouvelle solution
			auto it = std::find(newSolution.begin(), newSolution.end(), solution[indexSolution]);

			// Le polyedre n'est pas dans la solution courante
			if (it == newSolution.end())
				isSameSolution = false;

			indexSolution++;
		}

		// Nouvelle solution deja dans la liste
		if (isSameSolution)
			break;
	}

	return isSameSolution;
}