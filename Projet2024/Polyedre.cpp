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
vector<Face> Polyedre::getSharedFaces(const Polyedre& poly1, const Polyedre& poly2)
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



// GETTERS
int Polyedre::getId() const { return d_id; }

vector<Face> Polyedre::getFaces() const { return faces; }

Polyedre Polyedre::merge2Polyhedrons2D(const Polyedre& poly1, const Polyedre& poly2)
{
    Polyedre mergedPoly(-1);

    const Face& face1 = poly1.faces[0];
    const Face& face2 = poly2.faces[0];

    // Tester si faces coplanaires
    Point u = face1.d_sommets[1] - face1.d_sommets[0];
    Point v = face1.d_sommets.back() - face1.d_sommets[0];
    Point w = face2.d_sommets[1] - face2.d_sommets[0];
    bool areCoplanar = Plan::coplanarVectors(u, v, w);

 /*   cout << "coplanar ? : " << areCoplanar << endl;
    if (areCoplanar)
        cout << "coplanar " << endl;
    else 
        cout << "not coplanar " << endl;*/

    if (areCoplanar)    // Si les 2 faces sont coplanaires
    {
        int sameSegment = 0;    // 1 ou -1 si egale, 0 sinon
        auto it1 = face1.d_sommets.begin();
        auto it2 = face2.d_sommets.begin();
        while (it1 != face1.d_sommets.end()-1 && sameSegment==0)
        {
            while (it2 != face2.d_sommets.end() && sameSegment==0)
            {
                // 1 ou -1 si egale, 0 sinon
                auto nextIt1 = it1 + 1;
                auto nextIt2 = it2 + 1;
                sameSegment = Point::are2SegmentsEquals(*it1, *(nextIt1), *it2, *(nextIt2));

                ++it2;
            }
            ++it1;
        }

        --it1;
        //--it2;
        //cout << "end : " << *(face2.d_sommets.end()-1) << endl;
        if (it2 == face2.d_sommets.end() || it2 == face2.d_sommets.end()-1)
            it2 = face2.d_sommets.begin();
        else
            ++it2;

        if (sameSegment != 0)
        {   // FUSION

            mergedPoly = Polyedre(poly1);   // copie
            Point destination = *(it1 + 1);
            if (sameSegment == -1)
                destination = *it1;

            // Parcours de tous les sommets
            while (*it2 != destination)
            {                   
                if (sameSegment == 1)
                {
                    if (it2 == face2.d_sommets.begin())
                        it2 = face2.d_sommets.end()-1;
                    else
                        --it2;
                }
                else
                {
                    if (it2 == face2.d_sommets.end()-1)
                        it2 = face2.d_sommets.begin();
                    else
                        ++it2;
                }

                // Insertion des sommets de la 2ème faces
                // qui ne sont pas dans la 1ere
                if (*it2 != destination) {
                    cout << "it1 : " << *it1 << endl;
                    cout << "it1 suiv : " << *(it1+1) << endl;
                    mergedPoly.faces[0].d_sommets.insert(it1+1, *it2); // ERREUR ICI !!!!
                    ++it1;
                }
            }
        }
    }

    return mergedPoly;
}

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


// OPERATEURS

bool Polyedre::operator<(const Polyedre& otherPoly) const
{
    return d_id < otherPoly.d_id;
}

bool Polyedre::operator==(const Polyedre& poly) const
{
    // Liste des faces communes aux 2 polyedres
    vector<Face> sharedFaces = Polyedre::getSharedFaces(*this, poly);

    // S'il ont le même nombre de faces et qu'elles sont 
    //  toutes communes aux 2 polyedres
    if (this->faces.size() == poly.faces.size()
        && poly.faces.size() == sharedFaces.size())
    {
        return true;
    }
    return false;
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
