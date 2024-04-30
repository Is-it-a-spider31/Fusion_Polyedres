#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

#include "Point.h"
#include "Face.h"
#include "Polyhedre.h"
#include "Plan.h"


void decouper(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

void ecrireFichier(vector<Point> listePoints, vector<Polyedre> listePoly, string nomFichier)
{
    ofstream monFlux(nomFichier.c_str());

    if(monFlux)
    {
        monFlux << "# Blender 3.6.1" << endl;
        monFlux << "# www.blender.org" << endl;
        monFlux << "mtllib untitled.mtl" << endl;


        for(int i = 0; i < listePoints.size(); i++)
        {
            monFlux << "v " << listePoints[i].getX() << " " << listePoints[i].getY() << " " << listePoints[i].getZ() << endl;
        }


        for(int i = 0; i < listePoly.size(); i++)
        {
            monFlux << "o Polyedre" << i << endl;


            for(int j = 0; j < listePoly[i].faces.size(); j++)
            {
                vector<Point> interPoints = listePoly[i].faces[j].points;

                monFlux << "f ";

                for(int k = 0; k < interPoints.size(); k++)
                {
                    monFlux << interPoints[k].getId() << " ";
                }

                monFlux << endl;

            }
        }
    }
    else
    {
        // cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}


/*

for(int j = 0; j < listePoints.size(); j++)
            {
                monFlux << "v " << listePoints[j].getX() << " " << listePoints[j].getY() << " " << listePoints[j].getZ() << endl;
            }

*/

using namespace std;

int main(int argc, char* argv[])
{
    string nomFichier = "../../exemple3";

    stringstream strFichier ;
    strFichier << nomFichier;

    strFichier << ".obj";

    string nomFinal = strFichier.str();


    ifstream myfile (nomFinal);

    string mystring;

    bool objet = false;

    int indexPoint = 0;

    int indexFace = 0;

    int indexPoly= 0;


    vector<Point> listePoints;
    vector<Face> listeFaces;
    vector<Polyedre> listePoly;


    vector<Point> vecteurPointsInter;

    if ( myfile.is_open() )
    {

        while ( myfile.good() )
        {
            myfile >> mystring;

            if(mystring == "o" || objet == true)
            {
                // cout << "\n\n\n objet \n";
                myfile >> mystring;


                Polyedre polyedreInter(indexPoly);

                listePoly.push_back(polyedreInter);


                indexPoly++;
                objet = false;
            }
            if(mystring == "v")
            {
                // nouveau point

                double x = 0, y = 0, z = 0;

                myfile >> mystring;
                x = stold(mystring);

                myfile >> mystring;
                y = stold(mystring);

                myfile >> mystring;
                z = stold(mystring);

                indexPoint++;


                Point pointInter(indexPoint, x, y , z);

                listePoints.push_back(pointInter);
            }

            if(mystring == "vn")
            {
                //nouvelle normale  ( a voir si utilise ou non)
                /*
                // cout << "normale:  \n";
                myfile >> mystring;
                // cout << "x : " << mystring << "\n";
                myfile >> mystring;
                // cout << "y : " << mystring << "\n";
                myfile >> mystring;
                // cout << "z : " << mystring << "\n";
                */
            }
            if(mystring == "vt")
            {
                //nouvelle texture (pas utilisee pour le moment)
                /*
                // cout << "texture:  \n";
                myfile >> mystring;
                // cout << "1 : " << mystring << "\n";
                myfile >> mystring;
                // cout << "2 : " << mystring << "\n";
                */
            }




            // ###############################################################################################################################


            if(mystring == "f")
            {
                //nouvelle face de cet objet en cours

                // cout << "face:  \n";
                myfile >> mystring;

                while(mystring != "o" && myfile.good())
                {
                    if(mystring == "f")
                    {
                        if(vecteurPointsInter.size() != 0)
                        {
                            indexFace++;

                            Face faceInter(vecteurPointsInter, indexFace);

                            listeFaces.push_back(faceInter);

                            vecteurPointsInter.clear();

                            // NE FONCTIONNE PAS
                            // cout << indexPoint << endl;
                            listePoly[indexPoly-1].faces.push_back(faceInter);

                        }


                        // cout << "face:  \n";




                    }
                    else
                    {
                        vector<string> decoupage;

                        decouper(mystring, '/', decoupage);

                        // cout << "\n"  << decoupage[0] << " ";

                        vecteurPointsInter.push_back(listePoints[stoi(decoupage[0]) - 1]);

                    }

                    myfile >> mystring;
                }

                if(mystring == "o")
                {
                    if(vecteurPointsInter.size() != 0)
                    {
                        indexFace++;

                        Face faceInter(vecteurPointsInter, indexFace);

                        listeFaces.push_back(faceInter);

                        vecteurPointsInter.clear();

                        listePoly[indexPoly-1].faces.push_back(faceInter);

                    }

                    objet = true;
                }
            }
        }
        indexFace++;

        Face faceInter(vecteurPointsInter, indexFace);

        listeFaces.push_back(faceInter);

        vecteurPointsInter.clear();

        listePoly[indexPoly-1].faces.push_back(faceInter);




        // cout << "\n\n\n\n";


        // cout << "Points:";

        for(int i = 0 ; i < listePoints.size(); i++)
        {
            // cout << "Numero "<< i << "\n";

            // cout << listePoints[i].getId() << " ";
            // cout << listePoints[i].getX() << " ";
            // cout << listePoints[i].getY() << " ";
            // cout << listePoints[i].getZ() << " \n\n";
        }

        // cout << "\n\n Faces : ";

        for(int i = 0 ; i < listeFaces.size(); i++)
        {
            // cout << "\n face :" << i << " \n";

            vector<Point> interPoints = listeFaces[i].points;

            for(int j = 0; j < listeFaces[i].points.size(); j++)
            {
                // cout << interPoints[j].getId() << " ";
            }
        }

        // cout << "\n\n Poly : ";


        for(int i = 0 ; i < listePoly.size(); i++)
        {
            // cout << "\n Poly :" << i << " \n";

            vector<Face> interFaces = listePoly[i].faces;

            for(int j = 0; j < interFaces.size(); j++)
            {
                // cout << interFaces[j].getId() << " ";
            }
        }


        // cout << "\n\n";





        int minimumPolygones = 100000;


        vector<Polyedre> polyedresPermutes;


        vector<int> ordresPermutation;

        vector<double> comparaisons;

        vector<Polyedre> interListePoly;


        for(int i = 0 ; i < listePoly.size(); i++)
        {
            ordresPermutation.push_back(i);
        }


        cout << ordresPermutation.size() << endl;

        do { // pour chaque permutation

            polyedresPermutes.clear();


            // creer la suite de polyedre de cette permutation
            for(int i = 0; i < ordresPermutation.size(); i++)
            {
                 polyedresPermutes.push_back(listePoly[ordresPermutation[i]]);
            }



            Polyedre polyActuel = polyedresPermutes[0];
            Polyedre polySuivant(0);

            interListePoly.clear();


            int fusionOptimaleVerif = 1000;

            //while(polyedresPermutes.size() != fusionOptimaleVerif)
            //{

                fusionOptimaleVerif = polyedresPermutes.size();

                // parcours des polyedres pour tenter de les fusionner
                for(int m = 1; m <polyedresPermutes.size();  m++)
                {

                    polySuivant = polyedresPermutes[m];

                    vector<Face> facesEnCommun;

                    bool faceCommune;


                    for(int i = 0; i <polyActuel.faces.size(); i++)
                    {
                        for(int j = 0; j < polySuivant.faces.size(); j++)
                        {
                            if(polyActuel.faces[i] == polySuivant.faces[j])
                            {
                                facesEnCommun.push_back(polyActuel.faces[i]);
                            }
                        }
                    }



                    if(facesEnCommun.size() != 0)
                    {
                        bool convex = true;




                        for(int k = 0; k < polyActuel.faces.size(); k++)
                        {
                            comparaisons.clear();

                            faceCommune = false;

                            for(int i = 0 ; i < facesEnCommun.size(); i++)
                            {
                                if(polyActuel.faces[k] == facesEnCommun[i])
                                {
                                    faceCommune = true;
                                }
                            }


                            if(faceCommune == false)
                            {

                                Plan planComparaison(polyActuel.faces[k].points[0], polyActuel.faces[k].points[1],polyActuel.faces[k].points[2]);



                                // TEST DE CONVEXITE polyActuel
                                for(int i = 0; i < polyActuel.faces.size(); i++)
                                {
                                    for(int j = 0; j < polyActuel.faces[i].points.size();j++)
                                    {
                                        double valeurComparaison = planComparaison.pointPositionFromPlan(polyActuel.faces[i].points[j]);
                                        comparaisons.push_back(valeurComparaison);
                                    }
                                }

                                // TEST DE CONVEXITE polySuivant
                                for(int i = 0; i < polySuivant.faces.size();i++)
                                {
                                    for(int j = 0; j < polySuivant.faces[i].points.size(); j++)
                                    {
                                        double valeurComparaison = planComparaison.pointPositionFromPlan(polySuivant.faces[i].points[j]);
                                        comparaisons.push_back(valeurComparaison);
                                    }
                                }


                                bool positif = false;
                                bool negatif = false;

                                for(int i = 0; i < comparaisons.size(); i++)
                                {
                                    if(comparaisons[i] > 0)
                                    {
                                        positif = true;
                                    }
                                    else if(comparaisons[i] < 0)
                                    {
                                        negatif = true;
                                    }
                                }

                                if(positif && negatif)
                                {

                                    convex = false;

                                }
                            }
                        }


                        for(int k = 0; k < polySuivant.faces.size(); k++)
                        {
                            comparaisons.clear();

                            faceCommune = false;


                            for(int i = 0 ; i < facesEnCommun.size(); i++)
                            {
                                if(polySuivant.faces[k] == facesEnCommun[i])
                                {
                                    faceCommune = true;
                                }
                            }


                            if(faceCommune == false)
                            {

                                Plan planComparaison(polySuivant.faces[k].points[0],polySuivant.faces[k].points[1],polySuivant.faces[k].points[2]);




                                for(int i = 0; i < polyActuel.faces.size(); i++)
                                {
                                    for(int j = 0; j < polyActuel.faces[i].points.size();j++)
                                    {
                                        double valeurComparaison = planComparaison.pointPositionFromPlan(polyActuel.faces[i].points[j]);
                                        comparaisons.push_back(valeurComparaison);
                                    }
                                }

                                for(int i = 0; i < polySuivant.faces.size();i++)
                                {
                                    for(int j = 0; j < polySuivant.faces[i].points.size(); j++)
                                    {
                                        double valeurComparaison = planComparaison.pointPositionFromPlan(polySuivant.faces[i].points[j]);
                                        comparaisons.push_back(valeurComparaison);
                                    }
                                }


                                bool positif = false;
                                bool negatif = false;

                                for(int i = 0; i < comparaisons.size(); i++)
                                {
                                    if(comparaisons[i] > 0)
                                    {
                                        positif = true;
                                    }
                                    else if(comparaisons[i] < 0)
                                    {
                                        negatif = true;
                                    }
                                }

                                if(positif && negatif)
                                {
                                    convex = false;
                                }
                            }
                        }



                        if(convex)
                        {
                            // cout << polyActuel.getId() << " " << polySuivant.getId() <<   " convexe \n ";

                            //fusion

                            for(int n = 0 ; n < polySuivant.faces.size(); n++)
                            {
                                bool commune = false;

                                for(int o = 0; o < facesEnCommun.size(); o++)
                                {
                                    if(polySuivant.faces[n] == facesEnCommun[o])
                                    {
                                        commune = true;
                                    }
                                }

                               if(!commune)
                               {
                                    polyActuel.faces.push_back(polySuivant.faces[n]);
                               }

                            }

                        }
                        else
                        {
                            interListePoly.push_back(polyActuel);

                            polyActuel = polySuivant;

                            // cout << polyActuel.getId() << " " << polySuivant.getId() <<   " non convexe\n ";
                        }

                    }
                }




                interListePoly.push_back(polyActuel);
                interListePoly.push_back(polyedresPermutes[polyedresPermutes.size()-1]);



                polyedresPermutes.clear();

                for(int i = 0; i < interListePoly.size(); i++)
                {
                    polyedresPermutes.push_back(interListePoly[i]);
                }
            //}




            if(polyedresPermutes.size()< minimumPolygones)
            {
                stringstream str;


                minimumPolygones = polyedresPermutes.size();


                str << nomFichier;

                str << "Solution";

                str << minimumPolygones;

                str << "Polygones.obj";

                string nomFichier = str.str();



                ecrireFichier(listePoints, polyedresPermutes, nomFichier);
            }
        } while(next_permutation(ordresPermutation.begin(), ordresPermutation.end()));








        // cout << "\n\n";






    }
    else
    {
        // cout << "Impossible d'ouvrir le fichier";

    }


	return 0;
}


