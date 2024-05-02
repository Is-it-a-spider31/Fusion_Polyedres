#include "Algorithm.h"

#include <fstream>
#include <algorithm>
#include "OBJFileHandler.h"

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
			if (!sharedFaces.empty()) {

				if (currentPolyhedron.isConvex() && nextPolyhedron.isConvex()) 
				{	// Si les 2 polyedres sont convexes (cf. consignes du projet)

					// FUSION
					currentPolyhedron.mergeWith(nextPolyhedron);

				}
				else
				{	//Si les 2 polyedres ne sont pas convexes
					
				}
			}

		}

		permutedPolyhedrons.clear();
		mergedPolyhedrons.clear();

	} while (next_permutation(permutedPolyhedrons.begin(), permutedPolyhedrons.end()));
}