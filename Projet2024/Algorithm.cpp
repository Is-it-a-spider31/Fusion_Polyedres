#include "Algorithm.h"

#include <iostream>

#include <fstream>
#include <sstream>
#include <algorithm>
#include "OBJFileHandler.h"

#include <chrono>
#include <ctime>
#include <iomanip>

#include <cstdlib>
#include <string>


using namespace std;

/**
 * @brief Contructeur a partir d'un fichier .obj
 *
 * @param filename Nom du fichier .obj
*/
Algorithm::Algorithm(const string& filename) 
	: d_nbGraphUsage{0}, d_nbMergeTry{0}, d_objectiveValue{0}
{
	// Chargement des donnees a partir du fichier .obj
	OBJFileHandler::loadOBJ(d_vertices, d_faces, d_polyhedra, filename);

	// Calcul du graphe des fusiosn convexes
	initializeGraph();
	d_mergeGraph.calculateDiameter();
	cout << "DIAMETRE : " << d_mergeGraph.getDiameter() << endl;
	// cout << d_mergeGraph;	// Affichage du graphe
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
vector<Polyedre> Algorithm::mergeAlgorithm(vector<Polyedre> solution, int limitNbPoly)
{
	double sumDistances = 0.0;
	double nbConsecutiveMerges = 0;
	
	int initSolutionSize = solution.size();

	// Liste des polyedres avec fusion
	vector<Polyedre> mergedPolyhedra;

	// true : arreter la solution en cours car on a deja mieux
	bool stopCurrentSolution = false;

	bool end = false;
	// Tant qu'on arrive a reduire le nombre de fusions
	while (!end)
	{
		Polyedre currentPolyhedron = solution[0];
		Polyedre nextPolyhedron(0);

		int nextPolyId = 1;
		sumDistances = 0.0;

		// Pour chaque polyedres (sauf le premier), 
		//	tant que la solution courante n'est pas arretee
		while (nextPolyId < solution.size() && !stopCurrentSolution)
		{
			bool isMergeLegal = false;	// true : la fusion est possible et convexe
			nextPolyhedron = solution[nextPolyId];
			d_nbMergeTry++;

			bool isEdgeChecked = d_mergeGraph.isEdgeAlreadyChecked(
				currentPolyhedron.getId(),
				nextPolyhedron.getId()
			);

			// Si les 2 polyedres sont dans le graphe 
			// et que leur fusion a deja ete testee
			if (isEdgeChecked)
			{
				d_nbGraphUsage++;	// Pour les statistiques

				// Maj de la distance entre les 2 sommets qu'on a essaye de fusionner
				sumDistances += d_mergeGraph.calculateDistance(
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
					if (currentPolyhedron.getId().empty())
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
				// Fusion des 2 polyedres (id vide si impossible)
				Polyedre mergedPoly = Polyedre::merge2Polyhedra(
					currentPolyhedron,
					nextPolyhedron
				);

				// Indique que la fusion de ces 2 polyedres a ete testee
				d_mergeGraph.markEdgeAsChecked(
					currentPolyhedron.getId(),
					nextPolyhedron.getId()
				);

				// Si fusion effectuee
				if (!mergedPoly.getId().empty())
				{
					// Teste si fusion convexe
					mergedPoly.computeConvexity();
					if (mergedPoly.isConvex())	// Fusion convexe
					{
						// Mise a jour du graphe
						d_mergeGraph.addEdge(
							currentPolyhedron.getId(),	// 1er sommet de l'arete (polygone 1)
							nextPolyhedron.getId(),	// 2eme sommet de l'arete (polygone 2)
							mergedPoly		// Polyedre fusionne
						);

						// Maj de la distance entre les 2 sommets qu'on a essaye de fusionner
						sumDistances += d_mergeGraph.calculateDistance(
							currentPolyhedron.getId(),
							nextPolyhedron.getId()
						);

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
				// (limitNbPoly doit etre passe en parametre de la methode)
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

			if (mergedPolyhedra.size() < solution.size())
			{
				// On va refaire une iteration a partir des nouvelles fusions
				solution = mergedPolyhedra;
				mergedPolyhedra.clear();
			}
			else
			{
				// Plus de fusions possibles, on arrete l'algo
				end = true;
			}
		}
		else	// Si l'algo a ete arrete en cours d'execution, renvoie une liste vide
		{
			mergedPolyhedra.clear();
			end = true;
		}

	}	// While pas termine

	// EVALUATION
	//cout << endl << "------------------" << endl;
	// Calcul de la penalite penalite (d_sumDistances >= 1)
	// cout << "sum distances = " << sumDistances << endl;
	double penality = pow(sumDistances/d_mergeGraph.getDiameter()/ initSolutionSize, 2)/2;
	// cout << "Penalite : " << penality << endl;
	// Calcul de la recompense
	// cout << "Val reward avant calcul : " << reward << endl;

	double min = 0;
	double max = pow((initSolutionSize - 1), 1.35);
	double reward = 0.0;
	for (Polyedre& poly : mergedPolyhedra)
		reward += pow(poly.getNbComponents()-1, 1.35);

	reward = ((reward - min)/(max-min))*2;	// Normalisation
	// cout << "Recompense : " << reward << endl;
	// Evaluation de la soluion courante
	// cout << "nb poly : " << mergedPolyhedra.size() << endl;
	d_objectiveValue = 1 + (
		static_cast<double>(mergedPolyhedra.size()) 
		/ static_cast<double>(initSolutionSize)
		) + penality - reward;
	// cout << "Objectif = " << d_objectiveValue << endl;

	return mergedPolyhedra;
}

/**
 * @brief Creer un repertoire avec un nom unique.
 * Ce nom est compose du nombre de polyedre apres fusion et de
 * la date courante.
 *
 * @param currentDir Repertoire dans lequel on veut creer un sous-repertoire
 * @param solution Taille de la solution apres fusion
*/
void Algorithm::createRunDir(string currentDir, string solution)
{
	// Date courante
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);

	// Convertion acec le fuseau horaire local
	tm local_tm;
	localtime_s(&local_tm, &now_time);

	// Formatage de la date en une chaine de caracteres
	ostringstream oss;
	oss << put_time(&local_tm, "%Y-%m-%d-%H%M%S");

	const string fullPath = currentDir + "Run_Poly"+ solution + "_" + oss.str() + "/";
	d_fullFilePath = fullPath;

	string cmd = "mkdir " + convertToWindowsPath(fullPath);
	
	#ifdef __linux__ // OS Linux
		cmd = "mkdir -p ./" + fullPath;
	#endif

	// Convertion string en char* pour system()
	char* cstr = new char[cmd.length() + 1];    // Allocation de la memoire
	strcpy_s(cstr, cmd.length() + 1, cmd.c_str());  // Copie

	system(cstr);
}

/**
 * @brief Remplace les '/' d'un chemin avec des '\' (pour windows)
 * @param unixPath Chemin avec de '/'
 * @return Le chemin pour windows avec des '\'
*/
string Algorithm::convertToWindowsPath(const string& unixPath)
{
	string windowsPath = unixPath;
	for (char& c : windowsPath) {
		if (c == '/') {
			c = '\\';
		}
	}
	return windowsPath;
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
	// d_objectiveValue mis a jour dans la fonction 'mergeAlgorithm'
	mergeAlgorithm(solution);
	return d_objectiveValue;
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
	Polyedre poly1, poly2;	// Polyedres vides

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

				if (!mergedPoly.getId().empty())	// Fusion effectuee
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
			} // if poly1 & poly2 convexes

			// Indique que la fusion de ces 2 polyedres a ete testee
			d_mergeGraph.markEdgeAsChecked(poly1.getId(), poly2.getId());
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
