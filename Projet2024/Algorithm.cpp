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
 * @brief Algorithme de fusion d'une solution (liste de polyedres)
 *
 * Effectue les fusions possibles dans l'ordre pour
 * un ensemble de polyedres donnes.
 * On arrete l'Algorithme de fusion si le nombre de polyedres depasse
 * la limite fixee (si -1 alors pas de limite).
 *
 * @param solution  liste de polyedres
 * @param limitNbPoly Nombre limite de polyedres (-1 par defaut, pas de limite)
 * @return nombre polyedres apres fusions
*/
vector<Polyedre> Algorithm::mergeAlgorithm(const vector<Polyedre>& solution, int limitNbPoly)
{
	Polyedre currentPolyhedron = solution[0];
	Polyedre nextPolyhedron(0);

	// Liste des polyedres avec fusion
	vector<Polyedre> mergedPolyhedra;

	// true : arreter la solution en cours car on a deja mieux
	bool stopCurrentSolution = false;

	// Pour chaque polyedres (sauf le premier), 
	//	tant que la solution courante n'est pas arretee
	int nextPolyId = 1;
	while (nextPolyId < solution.size() && !stopCurrentSolution)
	{
		bool isMergeLegal = false;	// true : la fusion est possible et convexe
		nextPolyhedron = solution[nextPolyId];

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
		} // if 2 polyedres convexes

		if (!isMergeLegal)	// Si pas de fusion possible
		{	// pas de face commune OU au moins 1 poly pas convexes OU fusion pas convexe
			mergedPolyhedra.push_back(currentPolyhedron);
			currentPolyhedron = solution[nextPolyId];

			// Si on a deja une meilleur solution
			if (limitNbPoly != -1 && mergedPolyhedra.size() >= limitNbPoly)
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
	}
	else	// Si l'algo a ete arrete en cours d'execution, renvoie une liste vide
	{
		mergedPolyhedra.clear();
	}

	return mergedPolyhedra;
}


/**
 * @brief Fonction d'evaluation d'une solution
 *
 * Renvoie le nombre de polyedres resultants de l'Algorithme
 * de fusion.
 *
 * @param solution liste de polyedres
 * @return nombre de polyedres apres l'algo de fusion
*/
int Algorithm::evaluateSolution(const vector<Polyedre>& solution)
{
	return mergeAlgorithm(solution).size();
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
