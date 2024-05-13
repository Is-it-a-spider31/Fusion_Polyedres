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

    /*
    cout << "face 1 : " << endl;
    for (size_t i = 0; i < face1.d_sommets.size(); i++)
    {
        cout << "id : " << face1.d_sommets[i].getId() << endl;
        cout << "point : " << face1.d_sommets[i];
    }
    cout << endl << "face 2 : " << endl;
    for (size_t i = 0; i < face1.d_sommets.size(); i++)
    {
        cout << "id : " << face1.d_sommets[i].getId() << endl;
        cout << "point : " << face1.d_sommets[i];
    }
    */



    if (areCoplanar)    // Si les 2 faces sont coplanaires
    {
        int sameSegment = 0;    // 1 ou -1 si egale, 0 sinon
        int i = 0;
        int j = 0;
        while (i < face1.d_sommets.size() && sameSegment==0)
        {
            int nextI = i + 1;
            if (nextI >= face1.d_sommets.size())
                nextI = 0;

            while (j < face2.d_sommets.size() && sameSegment==0)
            {
                int nextJ= j + 1;
                if (nextJ >= face2.d_sommets.size())
                    nextJ = 0;

                // 1 ou -1 si egale, 0 sinon
                sameSegment = Point::are2SegmentsEquals(
                    face1.d_sommets[i], face1.d_sommets[nextI],   // P1
                    face2.d_sommets[j], face2.d_sommets[nextJ]    // P2
                );
                j++;
            }
            i++;
        }
        i--;
        j--;


        cout << "sameSegment : " << sameSegment << endl;
        cout << "sommet i : " << face1.d_sommets[i];
        cout << "sommet j : " << face2.d_sommets[j];

        if (sameSegment != 0)
        {   // FUSION

            // Si on depasse la taille de la liste, on reviens au premier element
            Point destination = face1.d_sommets[0];
            if (i+1 < face1.d_sommets.size()) 
                destination = face1.d_sommets[i + 1];

            if (sameSegment == -1)
            {
                if (j + 1 < face2.d_sommets.size())
                    j++;
                else
                    j = 0;
            }

            cout << "destination : " << destination;
            cout << "sommet j suivant : " << face2.d_sommets[j];
            cout << "i : " << i << endl;
            cout << "j : " << j << endl;


            mergedPoly = Polyedre(poly1);   // copie
            // Parcours de tous les sommets de la 2eme face
            while (face2.d_sommets[j] != destination)
            {                   
                if (sameSegment == 1)
                {
                    if (j <= 0)
                        j = face2.d_sommets.size()-1;
                    else
                        j--;
                }
                else
                {
                    if (j >= face2.d_sommets.size()-1)
                        j = 0;
                    else
                        j++;
                }

                // Insertion des sommets de la 2ème faces
                // qui ne sont pas dans la 1ere
                if (face2.d_sommets[j] != destination) {

                    mergedPoly.faces[0].d_sommets.insert(            
                        mergedPoly.faces[0].d_sommets.begin() + i+1,
                        //mergedPoly.faces[0].d_sommets[j]
                        face2.d_sommets[j]
                    );
                    cout << "insertion indice i = " << i << endl;
                    if (i < mergedPoly.faces[0].d_sommets.size() - 1)
                        i++;
                    else
                        i = 0;
                }
            }   // while 
        }   // if 1 segment en commun
    }   // if 2 faces coplanaires
    cout << "MERGED POLY" << endl;
    for (auto& face : mergedPoly.faces)
    {
        for (auto& p : face.d_sommets)
        {
            cout << p;
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
