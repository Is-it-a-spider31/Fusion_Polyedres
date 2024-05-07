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

    /**
     * @brief Algorithme principal de fusion
    */
    void run();

    //FONCTIONS DE TEST
    void test_Convexity();
    void test_WriteObj();
    void test_LoadObj();

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

    /**
     * @brief Verifie si une solution de l'algo de fusion a deja ete trouvee
     * 
     * Si la solution (ensemble de polyedres) courante est dans 
     * la liste des solutions, cela signifie que cette solution a deja 
     * ete calculee et trouvee par l'algo de fusion.
     * 
     * @param newSolution Solution courante de l'algo de fusion
     * @param solutions Liste des solutions deja trouvees
     * 
     * @return true Si la solution est presente dans la liste
    */
    static bool isSolutionAlreadyFinded(
        const vector<Polyedre>& newSolution,        // Nouvelle solution
        const vector<vector<Polyedre>>& solutions   // Liste des solutions trouvees
    );
};

