#pragma 

#include <vector>
#include <unordered_map>

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

    /**
     * @brief Ajoute un sommet au graphe
     * 
     * @param vertex Sommet a ajouter
    */
    void addVertex(int vertex);

    /**
     * @brief Ajoute une arete au graphe entre 2 sommets
     *
     * Les 2 sommets devraient deja etre dans le graphe
     *
     * @param vertex1 1er sommet
     * @param vertex2 2eme sommet
    */
    void addEdge(int vertex1, int vertex2);

    /**
     * @brief Renvoie la liste des voisins d'un sommet
     *
     * Le sommet devrait deja etre dans le graphe
     *
     * @param vertex Sommet dont on cherche les voisins
     * @return La liste des voisins
    */
    vector<int> getNeighbors(int vertex);

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
    int calculateDistance(int startVertex, int endVertex);
    
    /**
     * Calcule le diametre du graphe, cad la distance maximale
     * possible entre 2 sommets
     * 
     * @return La distance maximale possible entre 2 sommets
    */
    int calculateDiameter();

private:

    /**
     * @brief Associe a chaque sommet une liste de ses voisins
    */
    unordered_map<int, vector<int>> d_neighborsMap;

};

