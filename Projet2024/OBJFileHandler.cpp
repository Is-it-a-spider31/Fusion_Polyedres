#include "ObjFileHandler.h"

#include <fstream>
#include <iostream>
#include <sstream>

/**
 * @brief Ecriture de polyedres dans un fichier obj
 *
 * @param vertices Liste des sommets
 * @param polyhedrons Liste des polyedres
 * @param filename Nom du fichier
*/

void OBJFileHandler::writeOBJ(const vector<Point>& vertices, const vector<Polyedre>& polyhedrons, const string& filename)
{
    ofstream monFlux(filename.c_str());
    if (monFlux)    // ECRITURE
    {
        //SOMMETS
        for (const auto& v : vertices) {
            monFlux << v;
        }

        //POLYEDRE
        for (const auto& poly : polyhedrons) {
            monFlux << poly;
        }

        monFlux.close();

    }

    else // ECHEC DE L'ECRITURE
    {
        cerr << "ERROR - cannot write file : \"" << filename << "\"" << endl;
    }
}


/**
 * @brief Lecture des donnees depuis un fichier .obj
 *
 * @param vertices Liste des sommets
 * @param faces Liste des faces
 * @param polyhedrons Liste des polyedres
 * @param filename Nom du fichier
*/
void OBJFileHandler::loadOBJ(vector<Point>& vertices, vector<Face>& faces, vector<Polyedre>& polyhedrons, const string& filename)
{
    ifstream objFile(filename);

    string mystring;
    bool object = false;
    // Les indices commencent à 1 (selon le format OBJ)
    int indexVertex = 1;
    int indexFace = 1;

    int indexPoly = 0;
    vector<Point> currentVertices;

    if (objFile.is_open())
    {
        while (objFile.good())
        {
            objFile >> mystring;

            if (mystring == "o" || object == true)  // POLYEDRE
            {
                objFile >> mystring;
                Polyedre polyedreInter(indexPoly);
                polyhedrons.push_back(polyedreInter);
                indexPoly++;
                object = false;
            }
            if (mystring == "v")    // SOMMET (vertex)
            {
                // Coordonnes du sommet
                double x = 0, y = 0, z = 0;

                objFile >> mystring;
                x = stold(mystring);    // x
                objFile >> mystring;
                y = stold(mystring);    // y
                objFile >> mystring;
                z = stold(mystring);    // z

                Point currentVertex(indexVertex, x, y, z);
                indexVertex++;
                vertices.push_back(currentVertex);
            }
            if (mystring == "f")    // FACE
            {
                objFile >> mystring;

                // Parcours de toutes les faces du polyedre courant
                while (mystring != "o" && objFile.good())
                {
                    if (mystring == "f")    // Nouvelle face
                    {
                        if (currentVertices.size() != 0) 
                        {
                            Face currentFace(currentVertices, indexFace);
                            indexFace++;
                            faces.push_back(currentFace);
                            currentVertices.clear();
                            polyhedrons[indexPoly - 1].faces.push_back(currentFace);
                        }
                    }
                    else    // Face courante
                    {
                        vector<float> vertexData = vertexDataFromString(mystring, '/');
                        // Ajout du sommet a la face
                        currentVertices.push_back(vertices[vertexData[0] - 1]);
                    }
                    objFile >> mystring;
                }

                if (mystring == "o")    // POLYEDRE SUIVANT
                {
                    polyhedrons[indexPoly - 1].computeConvexity();

                    if (currentVertices.size() != 0)
                    {
                        Face currentFace(currentVertices, indexFace);
                        indexFace++;
                        faces.push_back(currentFace);
                        currentVertices.clear();
                        polyhedrons[indexPoly - 1].faces.push_back(currentFace);
                 
                    }
                    object = true;
                }
            }
        }

        // Ajout de la derniere face
        Face currentFace(currentVertices, indexFace);
        faces.push_back(currentFace);
        currentVertices.clear();
        polyhedrons[indexPoly - 1].faces.push_back(currentFace);
        polyhedrons[indexPoly - 1].computeConvexity();
    }
}

/**
 * @brief Permet d'extraire les donnees d'une face dans un tableau
 * 
 * Format d'une face :
 * f vertexId/textureId/normalId ...
 * 
 * Exemple :
 * f 9/15/7 10/16/7 12/17/7 11/18/7
 * on veut seulement les vertices :
 * f 9 10 12 11
 * 
 * @param str donnees d'une face
 * @param delim delimiteur "/"
 * 
 * @return tableau des donnees du sommet (en float)
*/
vector<float> OBJFileHandler::vertexDataFromString(string const& str, const char delim)
{
    vector<float> out;
    stringstream ss(str);
    string s;

    while (getline(ss, s, delim)) {
        out.push_back(stoi(s));
    }
    return out;
}
