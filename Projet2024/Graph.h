#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility> // Pour std::pair
#include <functional> // Pour std::hash

#include "Polyedre.h"

using namespace std;

/**
 * @brief Graphe non oriente des fusions convexes
 *
 * Represente le graphe non oriente des fusions possibles (convexes) 
 * pour un ensemble de polyedres.
 * 
 * Ainsi un sommet represente un polyedre, et une arete un fusion possible
*/
class Graph
{
public:

    Graph();

    void test();

    /**
     * @brief Ajoute un sommet au graphe
     * 
     * @param vertex Sommet a ajouter
    */
    void addVertex(const string vertex);

    /**
     * @brief Ajoute une arete au graphe entre 2 sommets
     *
     * Les 2 sommets devraient deja etre dans le graphe
     *
     * @param vertex1 1er sommet
     * @param vertex2 2eme sommet
     * @param mergedPoly Polyedre resultant de la fusion des 2 sommets
    */
    void addEdge(const string vertex1, const string vertex2, const Polyedre& mergedPoly);

    /**
     * @return true si le sommet est dans le graphe
    */
    bool isVertexInGraph(const string& vertex);

    /**
     * @return true si les 2 sommets sont voisins, false sinon
    */
    bool areVerticesNeighbors(const string& vertex1, const string& vertex2);

    /**
     * @brief Renvoie le polyedre resultant de la fusion des 2 sommets
     * 
     * @param vertex1 1er polyedre
     * @param vertex2 2eme polyedre
     * @return polyedre resultant de la fusion
    */
    Polyedre getEdgeWeight(const string& vertex1, const string& vertex2);

    /**
     * @brief Renvoie la distance entre deux sommets en utilisant BFS
     *
     * Les 2 sommets devraient deja etre dans le graphe
     * Si l'un des deux n'est pas dans le graphe, renvoie -1
     *
     * @param startVertex Sommet de depart
     * @param endVertex Sommet de fin
     * @return La distance entre les 2 sommets (ou -1)
    */
    int calculateDistance(const string& startVertex, const string& endVertex);
    
    /**
     * Renvoie le diametre du graphe, cad la distance entre
     * les 2 sommets les plus eloignes
     *
     * Complexite : O(nbSommets^2 x (nbSommets + nbAretes))
    */
    void calculateDiameter();

    /**
     * @return La distance maximale possible entre 2 sommets
    */
    int getDiameter();

    /**
     * @brief Marque une arete comme verifiee
     * @param vertex1 
     * @param vertex2 
    */
    void markEdgeAsChecked(const string& vertex1, const string& vertex2);

    /**
     * @return true si la fusion entre les 2 sommets a deja ete verifiee
    */
    bool isEdgeAlreadyChecked(const string& vertex1, const string& vertex2);

    // OPERATEUR
    /**
 * @brief Opérateur de flux de sortie pour les objets Graph.
 *
 * Affiche les informations du graphe dans un flux de sortie.
 *
 * @param os Le flux de sortie dans lequel le graphe est affiché.
 * @param p Le graphe à afficher.
 * @return Une référence au flux de sortie après l'affichage du graphe.
 */
    friend std::ostream& operator<<(std::ostream& os, const Graph& p);

private:


    /**
     * @brief Associe a chaque sommet la liste de ses voisins sans doublons
    */
    unordered_map<string, unordered_set<string>> d_neighborsMap;

    /**
     * @brief Permet d'utiliser 2 clefs dans une map
    */
    struct pair_hash {
        template <class T1, class T2>
        size_t operator () (const std::pair<T1, T2>& p) const {
            return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
        }
    };

    /**
     * @brief Associe a chaque arete (2 sommets) un polyedre  .  
     * 
     * Il s'agit du polyedre resultant de la fusion des 2 polyedres 
     * qui correspondent au sommets de l'arete
    */
    unordered_map<pair<string, string>, Polyedre, pair_hash> d_edgeWeights;

    /**
     * @brief Aretes dont la fusion des sommets a deja ete testee
    */
    unordered_set<pair<string, string>, pair_hash> d_checkedEdges;

    /**
     * @brief Distance maximale possible entre 2 sommets
    */
    int d_diameter;

    /**
     * @brief Ajoute un nouveau voisin a un sommet (et reciproquement)
     *
     * @param vertex Sommet
     * @param neigbhor Voisin a ajouter
    */
    void addNeighbor(string vertex, string neighbor);
};

