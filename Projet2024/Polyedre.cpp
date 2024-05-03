#include "Polyedre.h"

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
