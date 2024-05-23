#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Polyedre.h"

using namespace std;

/**
 * Represente le graphe non oriente des fusions possibles entre 2
 * elements atomiques d'un ensemble de polyedres.
 * 
 * Ainsi un sommet represente un polyedre, et une arete un fusion possible
*/
class Graph
{
public:

    void test();

    /**
     * @brief Ajoute un sommet au graphe
     * 
     * @param vertex Sommet a ajouter
    */
    void addVertex(const int vertex);

    /**
     * @brief Ajoute une arete au graphe entre 2 sommets
     *
     * Les 2 sommets devraient deja etre dans le graphe
     *
     * @param vertex1 1er sommet
     * @param vertex2 2eme sommet
     * @param mergedPoly Polyedre resultant de la fusion des 2 sommets
    */
    void addEdge(const int vertex1, const int vertex2, const Polyedre& mergedPoly);

    /**
     * @return true si le sommet est dans le graphe
    */
    bool isVertexInGraph(const int& vertex);

    /**
     * @return true si les 2 sommets sont voisins, false sinon
    */
    bool areVerticesNeighbors(const int& vertex1, const int& vertex2);

    /**
     * @brief Renvoie le polyedre resultant de la fusion des 2 sommets
     * 
     * @param vertex1 1er polyedre
     * @param vertex2 2eme polyedre
     * @return polyedre resultant de la fusion
    */
    Polyedre getEdgeWeight(const int& vertex1, const int& vertex2);

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
    int calculateDistance(const int& startVertex, const int& endVertex);
    
    /**
     * Calcule le diametre du graphe, cad la distance maximale
     * possible entre 2 sommets
     * 
     * @return La distance maximale possible entre 2 sommets
    */
    int calculateDiameter();

    // OPERATEUR

    friend std::ostream& operator<<(std::ostream& os, const Graph& p);

private:


    /**
     * @brief Associe a chaque sommet la liste de ses voisins sans doublons
    */
    unordered_map<int, unordered_set<int>> d_neighborsMap;

    /**
     * @brief Permet d'utiliser 2 clefs dans une map
    */
    struct pair_hash {
        template <class T1, class T2>
        size_t operator () (const std::pair<T1, T2>& p) const {
            auto hash1 = std::hash<T1>{}(p.first);
            auto hash2 = std::hash<T2>{}(p.second);
            return hash1 ^ hash2;
        }
    };

    /**
     * @brief Associe a chaque arete (2 sommets) un polyedre
     * 
     * Il s'agit du polyedre resultant de la fusion des 2 polyedres 
     * qui correspondent au sommets de l'arete
    */
    unordered_map<pair<int, int>, Polyedre, pair_hash> d_edgeWeights;

    /**
     * @brief Ajoute un nouveau voisin a un sommet
     *
     * @param vertex Sommet
     * @param neigbhor Voisin a ajouter
    */
    void addNeighbor(int vertex, int neighbor);
};

