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
	: d_nbGraphUsage{0}, d_nbMergeTry{0}, d_sumDistances{0}
{
	// Chargement des donnees a partir du fichier .obj
	OBJFileHandler::loadOBJ(d_vertices, d_faces, d_polyhedra, filename);

	// Calcul du graphe des fusiosn convexes
	initializeGraph();
	d_mergeGraph.calculateDiameter();
	//cout << d_mergeGraph;	// Affichage du graphe
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
	
	d_sumDistances = 0;

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
		d_nbMergeTry++;

		// Si les 2 polyedres sont dans le graphe, 
		//	cad que leur fusion a deja ete pre-calculee
		if (d_mergeGraph.isVertexInGraph(currentPolyhedron.getId())
			&& d_mergeGraph.isVertexInGraph(nextPolyhedron.getId()))
		{
			d_nbGraphUsage++;	// Pour les statistiques

			// Maj de la distance entre les 2 sommets qu'on essaye de fusionner
			d_sumDistances += d_mergeGraph.calculateDistance(
				currentPolyhedron.getId(),
				nextPolyhedron.getId()
			);

			// Indique si la fusion est possible
			isMergeLegal = d_mergeGraph.areVerticesNeighbors(
				currentPolyhedron.getId(),
				nextPolyhedron.getId()
			);

			if (isMergeLegal)	// Si la fusion est possible
			{
				// On recupere le polyedre fusionne pre-calcule
				currentPolyhedron = d_mergeGraph.getEdgeWeight(
					currentPolyhedron.getId(),
					nextPolyhedron.getId()
				);

				// Theoriquement, comme on a deja verifie que les 2 polyedres 
				//	sont voisins dans le graphe, on ne devrait jamais rencontrer ce cas.
				//	Cela signifierait un probleme dans la strcuture de donnees
				if (currentPolyhedron.getId() == -1)
				{
					isMergeLegal = false;
					cerr << "Graph::getEdgeWeight et Graph::areVerticesNeighbors "
						<< " ne sont pas coherents !" << endl
						<< "cf. Algorithm::mergeAlgorithm" << endl;
				}
			}
		}
		// Sinon, si les 2 polyedres sont convexes (cf. consignes du projet)
		else if (currentPolyhedron.isConvex() && nextPolyhedron.isConvex())
		{
			// Fusion des 2 polyedres (id = -1 si impossible)
			Polyedre mergedPoly = Polyedre::merge2Polyhedra(
				currentPolyhedron, 
				nextPolyhedron
			);
			//cout << "id = " << mergedPoly.getId() << endl;
			// Si fusion effectuee
			if (mergedPoly.getId() != -1)
			{	
				// Teste si fusion convexe
				mergedPoly.computeConvexity();
				if (mergedPoly.isConvex())	// Fusion convexe
				{
					currentPolyhedron = mergedPoly;
					isMergeLegal = true;
				}
			}
		} // if 2 polyedres convexes

		if (!isMergeLegal)	// Si pas de fusion possible
		{	// cad Pas de face commune 
			//	OU au moins 1 poly pas convexes 
			//	OU fusion pas convexe

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
		cout << "Somme des distances : " << d_sumDistances << endl;
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
double Algorithm::evaluateSolution(const vector<Polyedre>& solution)
{
	int size = mergeAlgorithm(solution).size();
	double objective =
		d_sumDistances / (d_mergeGraph.getDiameter() * (size - 1));
	return objective;
}

/**
 * Construit le graphe des fusions convexes
 * a partir de la liste des polyedres.
 * 
 * Complexite : O(n^2)
*/
void Algorithm::initializeGraph()
{
	vector<Face> sharedFaces;
	int size = d_polyhedra.size();
	Polyedre poly1(-1), poly2(-1);	// Polyedres vides

	int nbTestedMerge = 0;

	// Parcour de toutes les paires uniques de polyedres
	for (size_t i = 0; i < size - 1; i++)
	{
		poly1 = d_polyhedra[i];

		// Mise a jour du graphe avec un nouveau sommet/polyedre
		d_mergeGraph.addVertex(poly1.getId());

		for (size_t j = i+1; j < size; j++)
		{
			nbTestedMerge++;
			poly2 = d_polyhedra[j];

			if (poly1.isConvex() && poly2.isConvex())
			{
				// Fusion des 2 polyedres (id = -1 si impossible)
				Polyedre mergedPoly = Polyedre::merge2Polyhedra(poly1, poly2);

				if (mergedPoly.getId() != -1)	// Fusion effectuee
				{
					mergedPoly.computeConvexity();
					if (mergedPoly.isConvex())	// Fusion convexe
					{
						// Ajout de l'arete avec le polyedre associe
						d_mergeGraph.addEdge(
							poly1.getId(),	// 1er sommet de l'arete (polygone 1)
							poly2.getId(),	// 2eme sommet de l'arete (polygone 2)
							mergedPoly		// Polyedre fusionne
						);
					}
				}
			} // poly1 & poly2 convexes
		} // for

		// Ajout du dernier polyedre en tant que sommet du graphe
		d_mergeGraph.addVertex(poly2.getId());

	} // for
	cout << "Nombre de fusions testees dans le graphe : " << nbTestedMerge << endl;
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
