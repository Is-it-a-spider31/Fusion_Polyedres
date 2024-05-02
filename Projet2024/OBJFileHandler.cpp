#include "ObjFileHandler.h"

#include <fstream>
#include <sstream>
#include <iostream>

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
        monFlux << "# Blender 3.6.1" << endl;
        monFlux << "# www.blender.org" << endl;
        monFlux << "mtllib untitled.mtl" << endl;

        // Ecriture de tous les sommets
        for (int i = 0; i < vertices.size(); i++)
        {
            monFlux << "v " << vertices[i].getX() << " " << vertices[i].getY() << " " << vertices[i].getZ() << endl;
        }

        // Ecriture des polyhedrons
        for (int i = 0; i < polyhedrons.size(); i++)
        {
            monFlux << "o Polyedre" << i << endl;

            // Pour chaques faces du polyedre
            for (int j = 0; j < polyhedrons[i].faces.size(); j++)
            {
                vector<Point> sommets = polyhedrons[i].faces[j].d_sommets;

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
    int indexPoint = 0;
    int indexFace = 0;
    int indexPoly = 0;
    vector<Point> vecteurPointsInter;

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

                indexPoint++;
                Point currentVertex(indexPoint, x, y, z);
                vertices.push_back(currentVertex);
            }
            if (mystring == "f")    // FACE
            {
                //nouvelle face de cet object en cours
                objFile >> mystring;

                // Parcours de toutes les faces du polyedre courant
                while (mystring != "o" && objFile.good())
                {
                    if (mystring == "f") 
                    {
                        if (vecteurPointsInter.size() != 0)
                        {
                            indexFace++;

                            Face faceInter(vecteurPointsInter, indexFace);
                            faces.push_back(faceInter);

                            vecteurPointsInter.clear();
                            polyhedrons[indexPoly - 1].faces.push_back(faceInter);
                        }
                    }
                    else
                    {
                        vector<string> decoupage;
                        decouper(mystring, '/', decoupage);
                        // cout << "\n"  << decoupage[0] << " ";
                        vecteurPointsInter.push_back(vertices[stoi(decoupage[0]) - 1]);
                    }
                    objFile >> mystring;
                }

                if (mystring == "o")
                {
                    if (vecteurPointsInter.size() != 0)
                    {
                        indexFace++;
                        Face faceInter(vecteurPointsInter, indexFace);
                        faces.push_back(faceInter);
                        vecteurPointsInter.clear();
                        polyhedrons[indexPoly - 1].faces.push_back(faceInter);
                    }
                    object = true;
                }
            }
        }
        indexFace++;

        Face faceInter(vecteurPointsInter, indexFace);
        faces.push_back(faceInter);
        vecteurPointsInter.clear();
        polyhedrons[indexPoly - 1].faces.push_back(faceInter);
    }
}

void OBJFileHandler::decouper(string const& str, const char delim, vector<string>& out)
{
    stringstream ss(str);

    string s;
    while (getline(ss, s, delim)) {
        out.push_back(s);
    }
}
