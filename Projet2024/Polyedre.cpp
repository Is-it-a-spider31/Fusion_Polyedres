#include "Polyedre.h"
#include "Plan.h"

#include <iostream>

Polyedre::Polyedre(int id) : d_id(id) {}
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

int Polyedre::getId() const { return d_id; }

vector<Face> Polyedre::getFaces() const { return faces; }

bool Polyedre::isConvex() const { return d_isConvex; }

void Polyedre::computeConvexity()
{

    std::cout << faces.size() << std::endl;
    for (int i = 0; i < faces.size(); i++)
    {
        double seuil = 1e-3;
        Plan p = Plan(faces[i].d_sommets[0], faces[i].d_sommets[1], faces[i].d_sommets[2]);

        /*for (int j = 0; j < faces[i].d_sommets.size(); j++)
        {
            double sens_point = p.pointPositionFromPlan(faces[i].d_sommets[j]);
            std::cout << "  - Sommet " << j << " : " << sens_point << std::endl;
            if (sens_point != sens_reference)
            {
                //if (sens_point < sens_reference - seuil || sens_point > sens_reference + seuil)
                //{ 
                d_isConvex = false;
                return;
                //}
            }

        }*/

        for (int f = 0; f < faces.size(); f++)
        {
            double sens = 0;
            bool pos;
            std::cout << "  Face " << f << " : " << std::endl;
            for (int p2 = 0; p2 < faces[f].d_sommets.size(); p2++)
            {
                
                double sens_point = p.pointPositionFromPlan(faces[f].d_sommets[p2]);
                std::cout << "  - Sommet " << p2 << " : " << sens_point << " [ x: " << faces[f].d_sommets[p2].getX() << " y: " << faces[f].d_sommets[p2].getY() << " z : " << faces[f].d_sommets[p2].getZ() <<std::endl;
                if (p.pointPositionFromPlan(faces[f].d_sommets[p2]) != 0)
                {
                    if (sens == 0) {
                        sens = p.pointPositionFromPlan(faces[f].d_sommets[p2]);
                        pos = (sens >= 0);
                    }
                    else {
                        if (!(sens_point >= 0 && pos || sens_point <= 0 && !pos))
                        {
                            d_isConvex = false;
                            return;
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

std::ostream& operator<<(std::ostream& os, const Polyedre& p)
{
    os << "o Object" << p.getId() << std::endl;
    for (const auto& face : p.getFaces()) 
    {
        os << face;
    }
    os << std::endl;


    return os;
}
