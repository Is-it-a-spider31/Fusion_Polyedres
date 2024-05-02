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
	 * @brief Contructeur a partir des sommets
	 *
	 * @param sommets sommets de la face
	 * @param id identifiant unique de la face
	*/
	Algorithm(const string &filename);


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

