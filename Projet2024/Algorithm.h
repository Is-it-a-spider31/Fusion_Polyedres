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
 * @brief Classe abstraite, permet d'effectuer l'algo de fusion
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
     * @brief Permet de stocker et ecrire des donnees de l'algo
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

    virtual const string getFilePath() = 0;

    /**
     * @brief Creer un repertoire avec un nom unique.
     * Ce nom est compose du nombre de polyedre apres fusion et de
     * la date courante.
     * 
     * @param currentDir Repertoire dans lequel on veut creer un sous-repertoire
     * @param solution Taille de la solution apres fusion
    */
    void createRunDir(string currentDir, string solution);

    /**
     * @brief Remplace les '/' d'un chemin avec des '\' (pour windows)
     * @param unixPath Chemin avec de '/'
     * @return Le chemin pour windows avec des '\'
    */
    string convertToWindowsPath(const string& unixPath);

    /**
     * @brief Repertoire ou on ecrit les resultats de l'execution courante.
     * 
     * Chemin du repertoire vers lequel les resultats
     * de l'execution courante sont ecrits
    */
    string d_fullFilePath;

    /**
     * @brief Nombre de polyèdre total de la solution finale
     */
    int d_nb_poly_finale;

private:
    /**
     * Construit le graphe des fusions convexes
     * a partir de la liste des polyedres.
     *
     * Complexite : O(n^2)
    */
    void initializeGraph();
};

