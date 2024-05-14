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
	OBJFileHandler::loadOBJ(d_vertices, d_faces, d_polyhedra, filename);
}

/**
 * @brief Algorithme principal de fusion
*/
void Algorithm::run()
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
	int nbUniqueSolutions = 0;	// nombre de solutions uniques trouvees

	// Pour chaque combinaison de permutation
	//	(complexite n! pour n polyedres)
	do 
	{
		Polyedre currentPolyhedron = permutedPolyhedra[0];
		Polyedre nextPolyhedron(0);

		// true : arreter la solution en cours car on a deja mieux
		bool stopCurrentSolution = false;

		// Pour chaque polyedres (sauf le premier), 
		//	tant que la solution courante n'est pas arretee
		int nextPolyId = 1;
		while (nextPolyId < permutedPolyhedra.size() && !stopCurrentSolution)
		{
			bool isMergeLegal = false;	// true : la fusion est possible et convexe
			nextPolyhedron = permutedPolyhedra[nextPolyId];

			// Si les 2 polyedres sont convexes (cf. consignes du projet)
			if (currentPolyhedron.isConvex() && nextPolyhedron.isConvex())
			{	
				bool areMerged = false;
				Polyedre mergedPoly(0);

				// recherche des faces communes entre les 2 polyedres
				vector<Face> sharedFaces = Polyedre::getSharedFaces(currentPolyhedron, nextPolyhedron);

				if (!sharedFaces.empty())	// S'il y a au moins une face commune
				{
					// FUSION 2 Polyedres
					mergedPoly = Polyedre::merge2Polyhedra(
						currentPolyhedron,
						nextPolyhedron,
						sharedFaces
					);
					areMerged = true;

				}
				else	// Pas de faces communes
				{
					// Les 2 polyedres ont une seule face
					if (currentPolyhedron.faces.size() == nextPolyhedron.faces.size()
						&& currentPolyhedron.faces.size() == 1) 
					{
						// FUSION 2 Polygones (une seule face + face pas commune aux 2)
						mergedPoly = Polyedre::merge2Polygones(currentPolyhedron, nextPolyhedron);
						if (mergedPoly.getId() != -1)
						{
							areMerged = true;
						}
					}
				}

				// Si fusion effectuee, teste si convexe
				if (areMerged)
				{
					mergedPoly.computeConvexity();
					if (mergedPoly.isConvex())	// Fusion convexe
					{
						currentPolyhedron = mergedPoly;
						isMergeLegal = true;
					}
				}
			}

			if (!isMergeLegal)	// Si pas de fusion possible
			{	// pas de face commune OU au moins 1 poly pas convexes OU fusion pas convexe
				mergedPolyhedra.push_back(currentPolyhedron);
				currentPolyhedron = permutedPolyhedra[nextPolyId];

				// Si on a deja une meilleur solution
				if (mergedPolyhedra.size() >= minNbPolySolution)
				{
					stopCurrentSolution = true;
				}
			}

			nextPolyId++;
		}	// while

		if (!stopCurrentSolution)	// Solution calculee jusqu'au bout
		{
			// Ajout du dernier polyedre fusionne
			mergedPolyhedra.push_back(currentPolyhedron);

			// Nouveau nombre minimum de polyedre (<= au minimum precedent)
			minNbPolySolution = mergedPolyhedra.size();
			nbFullSolutions++;

			// Vrai si les meme fusions ont deja ete trouvees et ecrites dans un fichier obj
			bool isAlreadyFinded = Algorithm::isSolutionAlreadyFinded(mergedPolyhedra, solutions);
	
			if (!isAlreadyFinded)	// Si c'est une nouvelle solution
			{
				nbUniqueSolutions++;
				solutions.push_back(mergedPolyhedra);				
				permutationsId.push_back(nbPermutaions);
			}
		}

		// permutedPolyhedrons.clear(); // 1 seul itération si non commente (pour tester)
		mergedPolyhedra.clear();
		nbPermutaions++;

	} while (next_permutation(permutedPolyhedra.begin(), permutedPolyhedra.end()));
	
	//	ECRITURE DES MEILLEURES SOLUTIONS TROUVEES
	auto it = permutationsId.begin();
	for (vector<Polyedre>& solution : solutions)
	{
		if (solution.size() == minNbPolySolution)
		{
			// Conversion de la taille du vecteur en chaîne de caractères
			stringstream sizeStr;
			sizeStr << solution.size();

			// Ecriture du fichier OBJ pour cette solution
			string filename = "MergeTest/generated/FUSION." + sizeStr.str()
				+ "Poly_" + to_string(*it) + ".obj";
			OBJFileHandler::writeOBJ(d_vertices, solution, filename);
		}
		++it;
	}

	// Affichage des statistiques
	std::cout << "Nb permutations : " << nbPermutaions << endl;
	std::cout << "Nb full solutions : " << nbFullSolutions << endl;
	std::cout << "Nb solutions unique trouvees : " << nbUniqueSolutions << endl;
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


	for (int i = 0; i < d_polyhedra.size(); i++)
	{
		std::cout << "id : " << d_polyhedra[i].getId() << " ";
		if (d_polyhedra[i].isConvex())
		{
			std::cout << "is convex !" << std::endl;
		}
		else {
			std::cout << "is not convex !" << std::endl;
		}

	}

}

void Algorithm::test_Merge()
{
	// FUSION
}

void Algorithm::test_WriteObj()
{
	OBJFileHandler::writeOBJ(d_vertices, d_polyhedra, "WriteObjectTest/exit_object.obj");
}

void Algorithm::test_LoadObj()
{
	vector<Point> vertices;
	vector<Polyedre> polyedrons;
	vector<Face> faces;

	OBJFileHandler::loadOBJ(vertices, faces, polyedrons, "ConvexiTest/normal_sphere.obj");
	OBJFileHandler::writeOBJ(vertices, polyedrons, "WriteObjectTest/exit_object_from_read.obj");
}
