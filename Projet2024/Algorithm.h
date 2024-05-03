#pragma once

#include <vector>
#include "Point.h"
#include "Face.h"
#include "Polyedre.h"
#include <string>

using namespace std;

class Algorithm
{
public:

	/**
	 * @brief Contructeur a partir d'un fichier .obj
     * 
	 * @param filename Nom du fichier .obj
	*/
	Algorithm(const string &filename);

    void run();
    void test_Convexity();

private:
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
    vector<Polyedre> d_polyhedrons;

    // METHODES
        
};

