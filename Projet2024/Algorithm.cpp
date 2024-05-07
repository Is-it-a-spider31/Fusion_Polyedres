#include "Algorithm.h"

#include <iostream>

#include <fstream>
#include <sstream>
#include <algorithm>
#include "OBJFileHandler.h"

using namespace std;

/**
 * @brief Contructeur a partir d'un fichier .obj
 *
 * @param filename Nom du fichier .obj
*/
Algorithm::Algorithm(const string& filename)
{
	// Chargement des donnees a partir du fichier .obj
	OBJFileHandler::loadOBJ(d_vertices, d_faces, d_polyhedrons, filename);
}

/**
 * @brief Algorithme principal de fusion
*/
void Algorithm::run()
{
	// Liste des solutions uniques trouvees
	//	(une solution = ensemble de polyedres)
	vector<vector<Polyedre>> solutions;

	// Liste des polyedres permutes
	vector<Polyedre> permutedPolyhedrons; 

	// Copie de la liste des polyedres dans celle qui sera permutee
	for (int i = 0; i < d_polyhedrons.size(); i++)
	{
		permutedPolyhedrons.push_back(d_polyhedrons[i]);
	}

	// Liste des polyedres avec fusion
	vector<Polyedre> mergedPolyhedrons;

	// Solution avec le nombre minimum de polyedres
	int minNbPolySolution = permutedPolyhedrons.size();

	// Statistiques
	int nbPermutaions = 0;		// nombre de permuations effectuees
	int nbFullSolutions = 0;	// nombre de solutions qui ont ete calculees jusqu'au bout
	int nbUniqueSolutions = 0;	// nombre de solutions uniques trouvees

	// Pour chaque combinaison de permutation
	//	(complexite n! pour n polyedres)
	do 
	{
		Polyedre currentPolyhedron = permutedPolyhedrons[0];
		Polyedre nextPolyhedron(0);

		// true : arreter la solution en cours car on a deja mieux
		bool stopCurrentSolution = false;

		// Pour chaque polyedres (sauf le premier), 
		//	tant que la solution courante n'est pas arretee
		int nextPolyId = 1;
		while (nextPolyId < permutedPolyhedrons.size() && !stopCurrentSolution)
		{
			bool canMerge = false;	// true : la fusion est possible et convexe
			nextPolyhedron = permutedPolyhedrons[nextPolyId];

			// recherche des faces communes entre les 2 polyedres
			vector<Face> sharedFaces = Polyedre::getSharedFaces(currentPolyhedron, nextPolyhedron);			

			// S'il y a au moins une face commune
			if (!sharedFaces.empty()) 
			{
				if (currentPolyhedron.isConvex() && nextPolyhedron.isConvex()) 
				{	// Si les 2 polyedres sont convexes (cf. consignes du projet)

					// FUSION
					Polyedre mergedPoly = Polyedre::merge2Polyhedrons(
						currentPolyhedron, 
						nextPolyhedron, 
						sharedFaces
					);
					mergedPoly.computeConvexity();

					if (mergedPoly.isConvex())	// Fusion convexe
					{
						currentPolyhedron = mergedPoly;
						canMerge = true;
					}
				}
			}

			if (!canMerge)	// Si pas de fusion possible
			{	// pas de face commune OU au moins 1 poly pas convexes OU fusion pas convexe
				mergedPolyhedrons.push_back(currentPolyhedron);
				currentPolyhedron = permutedPolyhedrons[nextPolyId];

				// Si on a deja une meilleur solution
				if (mergedPolyhedrons.size() >= minNbPolySolution)
				{
					stopCurrentSolution = true;
				}
			}

			nextPolyId++;
		}	// while

		if (!stopCurrentSolution)	// Solution calculee jusqu'au bout
		{
			// Ajout du dernier polyedre fusionne
			mergedPolyhedrons.push_back(currentPolyhedron);

			// Nouveau nombre minimum de polyedre (<= au minimum precedent)
			minNbPolySolution = mergedPolyhedrons.size();
			nbFullSolutions++;

			// Vrai si les meme fusions ont deja ete trouvees et ecrites dans un fichier obj
			bool isAlreadyFinded = Algorithm::isSolutionAlreadyFinded(mergedPolyhedrons, solutions);
	
			if (!isAlreadyFinded)	// Si c'est une nouvelle solution
			{
				nbUniqueSolutions++;
				solutions.push_back(mergedPolyhedrons);

				// Conversion de la taille du vecteur en chaîne de caractères
				stringstream sizeStr;
				sizeStr << mergedPolyhedrons.size();

				// Ecriture du fichier OBJ pour cette solution
				string filename = "MergeTest/generated/FUSION." + sizeStr.str()
					+ "Poly_" + to_string(nbPermutaions) + ".obj";
				OBJFileHandler::writeOBJ(d_vertices, mergedPolyhedrons, filename);
			}
		}

		//permutedPolyhedrons.clear(); // 1 seul itération si non commente (pour tester)
		mergedPolyhedrons.clear();
		nbPermutaions++;

	} while (next_permutation(permutedPolyhedrons.begin(), permutedPolyhedrons.end()));

	// Affichage des statistiques
	std::cout << "Nb permutations : " << nbPermutaions << endl;
	std::cout << "Nb full solutions : " << nbFullSolutions << endl;
	std::cout << "Nb unique solutions : " << nbUniqueSolutions << endl;
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
bool Algorithm::isSolutionAlreadyFinded(
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


//FONCTIONS DE TEST

void Algorithm::test_Convexity()
{
	// OBJFileHandler::writeOBJ(d_vertices, d_polyhedrons, "ConvexiTest/generated/sphere_export.obj");
	std::cout << "Nombre de sommets : " << d_vertices.size() << std::endl;
	std::cout << "Nombre de faces : " << d_faces.size() << std::endl;


	for (int i = 0; i < d_polyhedrons.size(); i++)
	{
		std::cout << "id : " << d_polyhedrons[i].getId() << " ";
		if (d_polyhedrons[i].isConvex())
		{
			std::cout << "is convex !" << std::endl;
		}
		else {
			std::cout << "is not convex !" << std::endl;
		}

	}

}

void Algorithm::test_WriteObj()
{
	OBJFileHandler::writeOBJ(d_vertices, d_polyhedrons, "WriteObjectTest/exit_object_write.obj");
}

void Algorithm::test_LoadObj()
{
	vector<Point> vertices;
	vector<Polyedre> polyedrons;
	vector<Face> faces;

	OBJFileHandler::loadOBJ(vertices, faces, polyedrons, "ConvexiTest/normal_sphere.obj");
	OBJFileHandler::writeOBJ(vertices, polyedrons, "WriteObjectTest/exit_object_from_read.obj");
}
