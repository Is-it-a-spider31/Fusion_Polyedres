#include "Polyedre.h"
#include "Plan.h"

#include <iostream>

Polyedre::Polyedre(int id) : d_id(id), d_isConvex(true){}

/**
 * @brief Renvoie les faces communes entre 2 polyedres
 *
 * @param poly1
 * @param poly2
 * @return la liste des faces communes entre les 2 polyedres
*/
vector<Face> Polyedre::getSharedFaces(Polyedre& poly1, Polyedre& poly2)
{
    // Liste des faces communes aux 2 polyedres
    vector<Face> sharedFaces;

    // Compare toutes les faces entre elles
    for (int i = 0; i < poly1.faces.size(); i++)
    {
        for (int j = 0; j < poly2.faces.size(); j++)
        {
            if (poly1.faces[i] == poly2.faces[j])
            {
                sharedFaces.push_back(poly1.faces[i]);
            }
        }
    }
    return sharedFaces;
}

/**
 * @brief Fusionne le polyedre courant avec un autre polyedre
 *
 * @param otherPoly Autre polyedre avec lequel on veut fusionner
 * @param sharedFaces Liste des faces communes aux 2 polyedres
*/
void Polyedre::mergeWith(const Polyedre otherPoly, const vector<Face> sharedFaces)
{
    for (int n = 0; n < otherPoly.faces.size(); n++)
    {
        bool isSharedFace = false;
        int j = 0;
        // Cherche si la face courante est commune aux 2 polyedres
        while (j < sharedFaces.size() && !isSharedFace) 
        {
            if (otherPoly.faces[n] == sharedFaces[j])
            {
                isSharedFace = true;
            }
            j++;
        }

        // Fusion uniquement la face n'est pas commune aux 2 polyèdres
        if (!isSharedFace)
        {
            this->faces.push_back(otherPoly.faces[n]);
        }

    }
}

// OPERATEUR
bool Polyedre::operator<(const Polyedre& otherPoly) const
{
    return d_id < otherPoly.d_id;
}

// GETTERS
int Polyedre::getId() const { return d_id; }

bool Polyedre::isConvex() const { return d_isConvex; }

void Polyedre::computeConvexity()
{
    /*
    // https://www.geogebra.org/3d?lang=fr
    // plan Face 64
    Plan plan = Plan(
        Point(0, -0.535118, - 0.535118, 0.418850), // 15
        Point(1, -0.610461, - 0.431759, 0.431759), // 93
        Point(2, -0.664133, - 0.455302, 0.302983)  // 100
    );

    // Point bug
    Point D(3, -0.698026, 0.474400, 0.156091); // 113
    // Point E(4, 0.12, -2.58, 1);
    double resD = plan.pointPositionFromPlan(D);
    //double resE = plan.pointPositionFromPlan(E);

    std::cout << "  TEST PLAN - D : " << resD << std::endl;
    //std::cout << "  TEST PLAN - E : " << resE << std::endl;
    */

    std::cout << faces.size() << std::endl;
    for (int i = 0; i < faces.size(); i++)
    {
        Plan plan = Plan(faces[i].d_sommets[0], faces[i].d_sommets[1], faces[i].d_sommets[2]);
        double sens = 0;
        bool pos;

        for (int f = 0; f < faces.size(); f++)
        {
            for (int p2 = 0; p2 < faces[f].d_sommets.size(); p2++)
            {
                double sens_point = plan.pointPositionFromPlan(faces[f].d_sommets[p2]);
                // std::cout << "  - Sommet " << p2 << " : " << sens_point << std::endl;

                if (sens_point != 0 && abs(sens_point) > 0.00001)
                {
                    if (sens == 0) {
                        sens = sens_point;
                        pos = (sens > 0);
                      /*  std::cout << "NOUVELLE FACE" << std::endl;
                        std::cout << "Sens val : " << sens << std::endl;
                        std::cout << "Sens : " << pos << std::endl;*/
                    }
                    else {
                        if ( (   (sens_point > 0 && !pos) 
                            ||  (sens_point < 0 && pos))
                             && abs(sens_point) > 0.0001)
                        {
                            std::cout << "  Face reference : " << i << std::endl;
                            std::cout << "  Face bug : " << f << std::endl;
                            std::cout << "  Sommet bug : " << p2 << std::endl;
                            std::cout << "  Point X " << faces[f].d_sommets[p2].getX() << std::endl;
                            std::cout << "  Point Y " << faces[f].d_sommets[p2].getY() << std::endl;
                            std::cout << "  Point Z " << faces[f].d_sommets[p2].getZ() << std::endl;
                            std::cout << "  bool sens " << pos << std::endl;
                            std::cout << "  sens point " << sens_point << std::endl;
                            d_isConvex = false;
                            return;
                        }
                        else {
                            //std::cout << "  sens point " << sens_point << std::endl;
                        }
                    }

                }
            }
        }

    }
    std::cout << "c'est true normalement chef" << std::endl;
    d_isConvex = true;
    return;
}