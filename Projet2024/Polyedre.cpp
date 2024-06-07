#include "Polyedre.h"
#include "Plan.h"

#include <iostream>
#include <string>


/**
* Constructeur par defaut
*/
Polyedre::Polyedre() : d_id(""), d_isConvex(true) {}

/**
 * @brief Constructeur avec un identifiant
 *
 * @param id Identifiant unique
*/
Polyedre::Polyedre(int id) : d_id(to_string(id)), d_isConvex(true) 
{
    d_components.insert(id);
}

/**
 * Constructeur par copie en excluant des faces.
 * Donne un nouvel id unique au polyedre.
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
 * @brief Fusionne 2 polyedres adjacents (au moins une face commune).
 * 
 * Les 2 polyedres doivent avoir au moins une face commune.
 * La fusion fonctionne si les polyedres ont une seule face (volume nul)
 * 
 * @param poly1 1er polyedre
 * @param poly2 2eme polyedre
 * @param sharedFaces Liste des faces communes aux 2 polyedres
 * 
 * @return Le polyedre resultant de la fusion
*/
Polyedre Polyedre::merge2AdjacentPolyhedra(
    const Polyedre& poly1, 
    const Polyedre& poly2, 
    const vector<Face> sharedFaces
)
{
    // Si poly2 a une seule face (polygone)
    // la fusion est egale a poly1
    if (poly2.faces.size() <= 1)    
        return poly1;
    // Si poly1 a une seule face (polygone)
    // la fusion est egale a poly2
    if (poly1.faces.size() <= 1)
        return poly2;

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

/**
 * @brief Fusionne 2 polyedres si possible
 *
 * Si la fusion n'est pas possible, retourne un polyedre
 *	vide avec son id vide
 *
 * @param poly1
 * @param poly2
 * @return Le polyedre fusionne (id vide si pas possible)
*/
Polyedre Polyedre::merge2Polyhedra(const Polyedre& poly1, const Polyedre& poly2)
{
    // id vide par defaut (fusion pas effectuee)
    Polyedre mergedPoly;

    // recherche des faces communes entre les 2 polyedres
    vector<Face> sharedFaces = Polyedre::getSharedFaces(poly1, poly2);

    if (!sharedFaces.empty())	// S'il y a au moins une face commune
    {
        // Fusionne 2 polyedres
        mergedPoly = Polyedre::merge2AdjacentPolyhedra(
            poly1,
            poly2,
            sharedFaces
        );
        // Mise a jour de l'identifiant
        mergedPoly.updateIdAndCompnenents(poly1, poly2);
    }
    else	// Pas de faces communes
    {
        // Les 2 polyedres ont une seule face
        if (poly1.faces.size() == poly2.faces.size()
            && poly1.faces.size() == 1)
        {
            // Fusionne 2 polygones (polyedres volume nul)
            //	id = -1 si pas possible
            mergedPoly = Polyedre::merge2Polygones(poly1, poly2);
            // Mise a jour de l'identifiant
            mergedPoly.updateIdAndCompnenents(poly1, poly2);
        }
    }
    return mergedPoly;
}

/**
 * @brief Fusionne 2 polygones
 *
 * Un polygone est un polyedre avec un volume nul
 * (c'est-a-dire un polyedre avec une seule face)
 *
 * @param poly1
 * @param poly2
 * @return Le polygone resultant de la fusion (id vide si fusion impossible)
*/
Polyedre Polyedre::merge2Polygones(const Polyedre& poly1, const Polyedre& poly2)
{
    Polyedre mergedPoly;    // Id vide par defaut
    const Face& face1 = poly1.faces[0];
    const Face& face2 = poly2.faces[0];

    // Tester si faces coplanaires
    Point u = face1.d_sommets[1] - face1.d_sommets[0];
    Point v = face1.d_sommets.back() - face1.d_sommets[0];
    Point w = face2.d_sommets[1] - face2.d_sommets[0];
    bool areCoplanar = Plan::coplanarVectors(u, v, w);

    if (areCoplanar)    // Si les 2 faces sont coplanaires
    {
        int sameEdge = 0;    // 1 ou -1 si egales, 0 sinon
        // indice du sommet de la face 1 pour lequel on a trouve une arete commune
        int i = 0; 
        // indice du sommet de la face 2 pour lequel on a trouve une arete commune
        int j = 0;

        // CHERCHE UNE ARETE COMMUNE aux 2 faces
        while (i < face1.d_sommets.size() && sameEdge==0)
        {
            int nextI = (i + 1) % face1.d_sommets.size();
            j = 0;

            while (j < face2.d_sommets.size() && sameEdge==0)
            {
                int nextJ = (j + 1) % face2.d_sommets.size();

                // 1 ou -1 si egale, 0 sinon (pour sens du parours de la face)
                sameEdge = Point::are2EdgesEquals(
                    face1.d_sommets[i], face1.d_sommets[nextI],   // arete de la face 1
                    face2.d_sommets[j], face2.d_sommets[nextJ]    // arete de la face 2
                );
                j++;
            }
            i++;
        }
        i--;
        j--;

        // ARETE EN COMMUN
        if (sameEdge != 0)
        {   // FUSION

            // Determine a partir de quel sommet de la 1ere face
            // on doit areter la fusion
            Point destination = face1.d_sommets[(i + 1)% face1.d_sommets.size()];

            // j : determine a partir de quel sommet de la 2eme face
            // on doit commencer la fusion
            if (sameEdge == -1)
                j = (j + 1) % face2.d_sommets.size();

            mergedPoly = poly1;   // copie

            // Insertion des sommets de la 2ème faces dans la 1ere
            // si ils ne sont pas deja dans la 1er face
            // Parcours de tous les sommets de la 2eme face
            while (face2.d_sommets[j] != destination)
            {   
                // Sens du parcours de la 2eme face
                if (sameEdge == 1)
                {
                    if (j <= 0)
                        j = face2.d_sommets.size()-1;
                    else
                        j--;
                }
                else
                {
                    j = (j + 1) % face2.d_sommets.size();
                }

                // si le sommet n'est pas deja dans la 1er face
                if (face2.d_sommets[j] != destination) 
                {   // INSERTION D'UN NOUVEAU SOMMET

                    // i : determine a quel endroit de la 1er face
                    // on doit inserer le nouveau sommet
                    mergedPoly.faces[0].d_sommets.insert(            
                        mergedPoly.faces[0].d_sommets.begin() + i+1,
                        face2.d_sommets[j]
                    );

                    i = (i + 1) % mergedPoly.faces[0].d_sommets.size();
                }
            }   // while 
        }   // if arete en commun
    }   // if 2 faces coplanaires

    return mergedPoly;
}
  
/**
 * @brief Calcul si le polyedre est convexe ou pas.
 *
 * Pour savoir si un polyedre est convexe, le principe est de verifier
 * si pour chaque face, tous les sommets sont du meme cote.
 * Cette methode met a jour un attribut qui est accessible
 * avec la fonction @ref isConvexe (pour eviter de refaire le calcul)
*/
void Polyedre::computeConvexity()
{
    if (faces.size() == 1)  // POLYGONE (Poledre 2D, une seule face et volume nul)
    {
        d_isConvex = faces[0].isConvex();
        return;
    }

    // Pour chaques faces
    for (int i = 0; i < faces.size(); i++)
    {
        // Creation d'un plan a patir de 3 points de la face
        Plan plan = Plan(faces[i].d_sommets[0], faces[i].d_sommets[1], faces[i].d_sommets[2]);
        double sens = 0;    // sens de reference pour une face

        // Indique de quel cote est un sommet par rapport a une face
        // donc a gauche ou a droite
        bool pos;

        // Pour chaque face
        for (int f = 0; f < faces.size(); f++)
        {
            // Pour chaque sommet de la face
            for (int p2 = 0; p2 < faces[f].d_sommets.size(); p2++)
            {
                // si = 0 alors le sommet est sur le meme plan, donc pas utilisable
                // sinon indique de quel cote se trouve le sommet par rapport a la face courante
                //  selon si sa valeur est > 0 ou < 0
                double sens_point = plan.pointPositionFromPlan(faces[f].d_sommets[p2]);

                // Pour determiner le sens de reference, il faut etre sur que le point
                // n'est pas sur le plan, donc théoriquement different de 0
                // Ajout d'une marge d'erreur (exemple : 1.54 e-18 est considere comme 0)
                if (sens_point != 0 && abs(sens_point) > 0.00001)
                {
                    // Si sens de reference pas initilise
                    if (sens == 0) 
                    {   // Initialisation du sens de reference pour la face courante
                        sens = sens_point;  // sens de reference pour la face courante
                        pos = (sens > 0);   // a gauche ou a droite
                    }
                    else // On a deja un sens de reference
                    {
                        // Si le sommet courant n'est pas du meme cote que le sommet de reference
                        if ( (   (sens_point > 0 && !pos) 
                            ||  (sens_point < 0 && pos))
                             && abs(sens_point) > 0.0001)
                        {
                            d_isConvex = false; // Pas convexe
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

/**
 * @brief Met a jour l'id et les composants du polyedre.
 *
 * Met a jour l'ensemble des composants a partir de ceux des 2
 * polyedres en parametre.
 * Puis met a jour l'identifiant a partir de cet ensemble
 *
 * @param poly1
 * @param poly2
*/
void Polyedre::updateIdAndCompnenents(const Polyedre& poly1, const Polyedre& poly2)
{
    d_components.insert(
        poly1.d_components.begin(), 
        poly1.d_components.end()
    );
    d_components.insert(
        poly2.d_components.begin(), 
        poly2.d_components.end()
    );
    d_id = "0";
    for (int elem : d_components) {
        d_id += to_string(elem);
    }
}


// GETTERS & SETTERS

string Polyedre::getId() const { return d_id; }

string Polyedre::getMTL() const
{
    return d_texture;
}

vector<Face> Polyedre::getFaces() const { return faces; }

/**
 * @return Le nombre de sous-polyèdres qui composent le polyedre actuel
*/
int Polyedre::getNbComponents() const
{
    if (d_components.size() <= 1)
        return 1;
   
    int nbFusions = 0;
    for (Polyedre poly : d_components)
    {
        nbFusions += poly.getNbComponents();
    }
    return nbFusions;
}

void Polyedre::setMTL(string name)
{
    d_texture = "Texture/" + name + ".obj";
}

void Polyedre::setId(const int id)
{
    d_id = to_string(id);
}

bool Polyedre::isConvex() const { return d_isConvex; }


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
