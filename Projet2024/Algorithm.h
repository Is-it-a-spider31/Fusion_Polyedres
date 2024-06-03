#pragma once

#include <vector>
#include <string>

#include "Point.h"
#include "Face.h"
#include "Polyedre.h"
#include "Graph.h"
#include "ExportAlgoData.h"

using namespace std;

/**
 * @brief Classe abstraite, parent des classes d'algo des fusions
*/
class Algorithm
{
public:

    /**
     * @brief Contructeur a partir d'un fichier .obj
     *
     * @param filename Nom du fichier .obj
    */
    Algorithm(const string &filename);

    /**
     * @brief Algorithme principal de fusion.
     * Methode abstraite !
    */
    virtual void run() = 0;

    /**
     * @brief Fonction d'evaluation d'une solution.
     * 
     * Renvoie le nombre de polyedres resultants de l'Algorithme
     * de fusion.
     * 
     * @param solution liste de polyedres
     * @return nombre de polyedres apres l'algo de fusion
    */
    double evaluateSolution(const vector<Polyedre>& solution) ;

    //FONCTIONS DE TEST
    void test_Convexity();
    void test_WriteObj();
    void test_LoadObj();

protected:
    // ATTRIBUTES

    /**
     * @brief Liste des sommets
    */
    vector<Point> d_vertices;

    /**
     * @brief Liste des faces
    */
    vector<Face> d_faces;

    /**
     * @brief Liste des polyedres
    */
    vector<Polyedre> d_polyhedra;

    /**
     * @brief Graphe des fusions convexes entre les polyedres
    */
    Graph d_mergeGraph;

    /**
     * @brief Nombre de fois que le graphe des fusions a ete utilise
    */
    int d_nbGraphUsage;

    /**
     * @brief Nombre de fusions testees
    */
    int d_nbMergeTry;

    /**
     * @brief Valeur de l'evaluation de la derniere solution calculee
    */
    double d_objectiveValue;

    /**
     * @brief Permet de stocker et ecrire des donnes de l'algo
    */
    vector<ExportAlgoData> d_dataWriters;


    /**
     * @brief Algorithme de fusion d'une solution (liste de polyedres).
     *
     * Effectue les fusions possibles dans l'ordre pour
     * un ensemble de polyedres donnes.
     * On arrete l'Algorithme de fusion si le nombre de polyedres depasse
     * la limite fixee (si -1 alors pas de limite).
     *
     * @param solution  liste de polyedres
     * @param limitNbPoly Nombre limite de polyedres (-1 par defaut, pas de limite)
     * @param nbGraphUsage Nombre de fois que le graphe des fusions a ete utilise
     * @return nombre de polyedres apres fusions
    */
    vector<Polyedre> mergeAlgorithm(vector<Polyedre> solution, int limitNbPoly = -1);

private:
    /**
     * Construit le graphe des fusions convexes
     * a partir de la liste des polyedres.
     *
     * Complexite : O(n^2)
    */
    void initializeGraph();
};

