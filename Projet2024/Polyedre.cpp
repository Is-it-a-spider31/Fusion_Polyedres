#include "Polyedre.h"
#include "Plan.h"

#include <iostream>

/**
 * @brief Constructeur par defaut
 *
 * @param id Identifiant unique
*/
Polyedre::Polyedre(int id) : d_id(id), d_isConvex(true){}


/**
 * @brief Constructeur par copie
 *
 * @param copy Polyedre a copier
*/
Polyedre::Polyedre(const Polyedre& copy)
{
    this->d_id = copy.d_id;
    this->d_isConvex = copy.d_isConvex;

    for (const Face faceCopy: copy.faces)
    {
        this->faces.push_back(faceCopy);
    }
}

/**
 * @brief Constructeur par copie en excluant des faces
 *
 * @param copy Polyedre a copier
 * @param sharedFaces Faces a ne pas copier
*/
Polyedre::Polyedre(const Polyedre& copy, const vector<Face>& excludedFaces)
{
    this->d_id = copy.d_id;
    this->d_isConvex = copy.d_isConvex;

    // Pour chaque face à copier
    int i = 0;
    for (const Face faceCopy : copy.faces)
    {
        // Cherche si la face est dans la liste des faces a ne pas copier
        auto it = std::find(excludedFaces.begin(), excludedFaces.end(), faceCopy);

        if (it == excludedFaces.end()) 
        {   // si la face n'est pas dans la liste des faces exclues
            this->faces.push_back(faceCopy);
        }
    }
}

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
Polyedre Polyedre::merge2Polyhedrons(const Polyedre& poly1, const Polyedre& poly2, const vector<Face> sharedFaces)
{
    Polyedre mergedPoly(poly1, sharedFaces);

    for (int n = 0; n < poly2.faces.size(); n++)
    {
        // Cherche si la face est dans la liste des faces communes
        auto it = std::find(sharedFaces.begin(), sharedFaces.end(), poly2.faces[n]);

        // Fusion uniquement la face n'est pas commune aux 2 polyèdres
        if (it == sharedFaces.end())
        {
            mergedPoly.faces.push_back(poly2.faces[n]);
        }

    }
    return mergedPoly;
}

// OPERATEUR
bool Polyedre::operator<(const Polyedre& otherPoly) const
{
    return d_id < otherPoly.d_id;
}

// GETTERS
int Polyedre::getId() const { return d_id; }

vector<Face> Polyedre::getFaces() const { return faces; }

bool Polyedre::isConvex() const { return d_isConvex; }

void Polyedre::computeConvexity()
{
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

                // Pour determiner le sens de reference, il faut etre sur que le point
                // n'est pas sur le plan, donc théoriquement different de 0
                // Ajout d'une marge d'erreur (exemple : 1.54 e-18 est considere comme 0)
                if (sens_point != 0 && abs(sens_point) > 0.00001)
                {
                    if (sens == 0) {
                        sens = sens_point;
                        pos = (sens > 0);
                    }
                    else {
                        if ( (   (sens_point > 0 && !pos) 
                            ||  (sens_point < 0 && pos))
                             && abs(sens_point) > 0.0001)
                        {
                            d_isConvex = false;
                            return;
                        }
                    }
                }   // if
            }   // for
        }   // for
    }   // for
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
