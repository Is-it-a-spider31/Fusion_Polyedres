#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "utils.h"
#include "Point.h"
#include "Polyedre.h"

using namespace std;

/**
 * @brief Ecritue de polyedres dans un fichier obj
 * 
 * @param points liste des vertices
 * @param polyedres listes des polyedres
 * @param filename nom du fichier a enregistrer
*/
void writeObjFile(vector<Point> points, vector<Polyedre> polyedres, string filename) 
{
    ofstream monFlux(filename.c_str());

    if (monFlux)    // ECRITURE
    {
        monFlux << "# Blender 3.6.1" << endl;
        monFlux << "# www.blender.org" << endl;
        monFlux << "mtllib untitled.mtl" << endl;

        // Ecriture de tous les points (vertices)
        for (int i = 0; i < points.size(); i++)
        {
            monFlux << "v " << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << endl;
        }

        // Ecriture des polyedres
        for (int i = 0; i < polyedres.size(); i++)
        {
            monFlux << "o Polyedre" << i << endl;

            // Pour chaques faces du polyedre
            for (int j = 0; j < polyedres[i].faces.size(); j++)
            {
                vector<Point> sommets = polyedres[i].faces[j].d_sommets;

                // Ecriture des sommets (leur identifiant) associes a la face
                monFlux << "f ";
                for (int k = 0; k < sommets.size(); k++)
                {
                    monFlux << sommets[k].getId() << " ";
                }

                monFlux << endl;
            }
        }
    }
    else    // ECHEC DE L'ECRITURE
    {
        cerr << "ERROR - cannot write file : \"" << filename << "\"" << endl;
    }
}