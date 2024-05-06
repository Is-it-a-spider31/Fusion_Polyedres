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

	// Pour chaque combinaison de permutation
	//	(complexite n! pour n polyedres)
	int nbPermutaions = 0;
	do {

		Polyedre currentPolyhedron = permutedPolyhedrons[0];
		Polyedre nextPolyhedron(0);

		// Pour chaque polyedres (sauf le premier)
		for (int nextPolyId = 1; nextPolyId < permutedPolyhedrons.size(); nextPolyId++)
		{
			nextPolyhedron = permutedPolyhedrons[nextPolyId];

			// recherche des faces communes entre les 2 polyedres
			vector<Face> sharedFaces = Polyedre::getSharedFaces(currentPolyhedron, nextPolyhedron);			

			// S'il y a au moins une face commune
			if (!sharedFaces.empty()) 
			{
				if (currentPolyhedron.isConvex() && nextPolyhedron.isConvex()) 
				{	// Si les 2 polyedres sont convexes (cf. consignes du projet)

					// FUSION
					Polyedre mergedPoly = Polyedre::merge2Polyhedrons(currentPolyhedron, nextPolyhedron, sharedFaces);
					mergedPoly.computeConvexity();

					if (mergedPoly.isConvex())	// Fusion convexe
					{
						currentPolyhedron = mergedPoly;
					}
					else	// Fusion pas convexe
					{
						mergedPolyhedrons.push_back(currentPolyhedron);
						currentPolyhedron = permutedPolyhedrons[nextPolyId];
					}
				}
				else
				{	//Si les 2 polyedres ne sont pas convexes
					mergedPolyhedrons.push_back(currentPolyhedron);
					currentPolyhedron = permutedPolyhedrons[nextPolyId];
				}
			}
			else // Aucune face en commun
			{
				mergedPolyhedrons.push_back(currentPolyhedron);
				currentPolyhedron = permutedPolyhedrons[nextPolyId];
			}
		}	// for

		// Ajout du dernier polyedre fusionne
		mergedPolyhedrons.push_back(currentPolyhedron);
		
		// Conversion de la taille du vecteur en chaîne de caractères
		stringstream sizeStr;
		sizeStr << mergedPolyhedrons.size();

		// ECRITURE DU FICHIER OBJ POUR CETTE PERMUTATION
		string filename = "MergeTest/generated/FUSION." + sizeStr.str() + "Poly_" + to_string(nbPermutaions)+".obj";
		OBJFileHandler::writeOBJ(d_vertices, mergedPolyhedrons,	filename);

		// permutedPolyhedrons.clear(); // 1 seul itération si décommenté (pour tester)
		mergedPolyhedrons.clear();
		nbPermutaions++;

	} while (next_permutation(permutedPolyhedrons.begin(), permutedPolyhedrons.end()));

	cout << "Nb permutations : " << nbPermutaions << endl;
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
