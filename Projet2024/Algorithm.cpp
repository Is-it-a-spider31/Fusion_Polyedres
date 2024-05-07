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

	// Pour chaque combinaison de permutation
	//	(complexite n! pour n polyedres)
	int nbPermutaions = 0;
	int nbFullSolutions = 0;	// nombre de solutions qui ont ete calculees jusqu'au bout
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

			// Conversion de la taille du vecteur en chaîne de caractères
			stringstream sizeStr;
			sizeStr << mergedPolyhedrons.size();

			// ECRITURE DU FICHIER OBJ POUR CETTE PERMUTATION
			string filename = "MergeTest/generated/FUSION." + sizeStr.str() 
				+ "Poly_" + to_string(nbPermutaions) + ".obj";
			OBJFileHandler::writeOBJ(d_vertices, mergedPolyhedrons, filename);
		}

		//permutedPolyhedrons.clear(); // 1 seul itération si non commente (pour tester)
		mergedPolyhedrons.clear();
		nbPermutaions++;

	} while (next_permutation(permutedPolyhedrons.begin(), permutedPolyhedrons.end()));

	std::cout << "Nb permutations : " << nbPermutaions << endl;
	std::cout << "Nb full solutions : " << nbFullSolutions << endl;
}

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
	OBJFileHandler::writeOBJ(d_vertices, d_polyhedrons, "WriteObjectTest/exit_object.obj");
}

void Algorithm::test_LoadObj()
{
	vector<Point> vertices;
	vector<Polyedre> polyedrons;
	vector<Face> faces;

	OBJFileHandler::loadOBJ(vertices, faces, polyedrons, "ConvexiTest/normal_sphere.obj");
	OBJFileHandler::writeOBJ(vertices, polyedrons, "WriteObjectTest/exit_object_from_read.obj");
}
