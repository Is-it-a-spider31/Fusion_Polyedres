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

    int evaluateSolution(const vector<Polyedre>& solution);

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

