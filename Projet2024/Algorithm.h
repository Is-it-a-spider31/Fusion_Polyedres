#pragma once

#include <vector>
#include "Point.h"
#include "Face.h"
#include "Polyedre.h"
#include <string>

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
     * @brief Algorithme principal de fusion
     * Methode abstraite !
    */
    virtual void run() = 0;

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
    vector<Polyedre> mergeAlgorithm(const vector<Polyedre>& solution, int limitNbPoly=-1);

    /**
     * @brief Fonction d'evaluation d'une solution
     * 
     * Renvoie le nombre de polyedres resultants de l'Algorithme
     * de fusion.
     * 
     * @param solution liste de polyedres
     * @return nombre de polyedres apres l'algo de fusion
    */
    int evaluateSolution(const vector<Polyedre>& solution) ;

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
};

