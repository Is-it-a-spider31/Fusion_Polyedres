#include "Graph.h"

#include <iostream>
#include <queue>
#include <string>

Graph::Graph() : d_diameter{-1} {}

void Graph::test()
{
    // cf. dessin papier
    // Les sommets sont ajoutes automatiquement
    Polyedre p(-1);
    addEdge(1, 2, p);
    addEdge(2, 3, p);
    addEdge(3, 4, p);
    addEdge(3, 5, p);
    addEdge(1, 5, p);
    addEdge(1, 5, p);
    addEdge(6, 5, p);
    addEdge(1, 6, p);

    /*cout << "Distance of the graph: " << calculateDistance(2, 4) << endl;
    cout << "Distance of the graph: " << calculateDistance(6, 2) << endl;*/

    //cout << "Diametter of the graph: " << calculateDiameter(6, 2) << endl;
}

/**
 * @brief Ajoute un sommet au graphe
 * 
 * Ne fait rien si le sommet est deja dans le graphe
 *
 * @param vertex Sommet a ajouter
*/
void Graph::addVertex(const int vertex)
{
    // Si le sommet n'est pas deja dans le graphe
    if (d_neighborsMap.find(vertex) == d_neighborsMap.end())
    {
        d_neighborsMap[vertex] = unordered_set<int>();  // Ajout du sommet
    }
}

/**
 * @brief Ajoute une arete au graphe entre 2 sommets
 * 
 * Si les sommets ne sont pas dans le graphe, ils sont ajoutes
 * Garde en memoire le resultat de la fusion des 2 polyedres
 *  aux sommets de l'arete
 *
 * @param vertex1 1er sommet
 * @param vertex2 2eme sommet
 * @param mergedPoly Polyedre resultant de la fusion des 2 sommets
*/
void Graph::addEdge(const int vertex1, const int vertex2, const Polyedre& mergedPoly)
{
    if (vertex1 == vertex2)
        return;

    // Ajout des sommets s'ils ne sont pas dans le graphe 
    addVertex(vertex1);
    addVertex(vertex2);
    addVertex(mergedPoly.getId());

    // Mise a jour des voisins (dans les 2 sens)
    addNeighbor(vertex1, vertex2);

    // Association du polyedre fusionne a l'arete
    d_edgeWeights[{vertex1, vertex2}] = mergedPoly;
    d_edgeWeights[{vertex2, vertex1}] = mergedPoly;
    
    // Marquer les aretes suivantes comme verifiees
    markEdgeAsChecked(vertex1, mergedPoly.getId());
    markEdgeAsChecked(vertex2, mergedPoly.getId());
}

/**
 * @return true si le sommet est dans le graphe
*/
bool Graph::isVertexInGraph(const int& vertex)
{
    if(d_neighborsMap.find(vertex) != d_neighborsMap.end())
        return true;
    return false;
}

/**
 * @brief Ajoute un nouveau voisin a un sommet (et reciproquement)
 *
 * @param vertex Sommet
 * @param neigbhor Voisin a ajouter
*/
void Graph::addNeighbor(int vertex, int neighbor)
{
    // Insertion du voisin s'il n'est pas deja dans la liste
    // (Rappel : d_neighborsMap[vertex] est un set, pas de doublons)
    d_neighborsMap[vertex].insert(neighbor);
    d_neighborsMap[neighbor].insert(vertex);

    // Marque l'arete comme verifiee
    markEdgeAsChecked(vertex, neighbor);
}

/**
 * @return true si les 2 sommets sont voisins, false sinon
*/
bool Graph::areVerticesNeighbors(const int& vertex1, const int& vertex2)
{
    bool areNeighbors = false;
    // Si les sommets sont dans le graphe
    if (d_neighborsMap.find(vertex1) != d_neighborsMap.end())
    {   
        // Si le sommet 2 est dans la liste des voisins du sommet 1
        if (d_neighborsMap[vertex1].find(vertex2) != d_neighborsMap[vertex1].end())
            areNeighbors = true;
    }
    return areNeighbors;
}

/**
 * @brief Renvoie le polyedre resultant de la fusion des 2 sommets
 *
 * @param vertex1 1er polyedre
 * @param vertex2 2eme polyedre
 * @return polyedre resultant de la fusion
*/
Polyedre Graph::getEdgeWeight(const int& vertex1, const int& vertex2)
{
    Polyedre mergedPoly(-1);

    // Creation d'une paire de clefs correspondant a une arete
    pair<int, int> myPair = std::make_pair(vertex1, vertex2);

    // Verification si la paire de cles a ete trouvee
    auto it = d_edgeWeights.find(myPair);
    if (it != d_edgeWeights.end()) 
    {
        // Acces au polyedre associe a l'arete
        mergedPoly = d_edgeWeights[myPair];
    }
    return mergedPoly;
}

/**
 * @brief Renvoie la distance entre deux sommets en utilisant BFS
 * 
 * Les 2 sommets doivent deja etre dans le graphe
 * Si l'un des deux n'est pas dans le graphe, renvoie -1
 * 
 * Complexite : O(nbSommets + nbAretes)
 *
 * @param startVertex Sommet de depart
 * @param endVertex Sommet de fin
 * @return La distance entre les 2 sommets (ou -1)
*/
int Graph::calculateDistance(const int& startVertex, const int& endVertex)
{
    // Si au moins un des deux sommets n'est pas dans le graphe
    if (d_neighborsMap.find(startVertex) == d_neighborsMap.end() 
        || d_neighborsMap.find(endVertex) == d_neighborsMap.end()) 
    {
        return -1;
    }

    // Associe a chaque sommet sa distance 
    //  avec le sommet de debut (-1 par defaut)
    unordered_map<int, int> distancesMap; 

    // File d'attente des sommets a traiter,
    //  cad les sommets dont on doit calculer la distance de leurs voisins
    queue<int> verticesToProcess;           

    // Initialisation des distances a -1 pour indiquer
    //  q'elles ne sont pas encore calculees.
    // En effet, tous les distances calculees seront forcement > 0
    for (const auto& pair : d_neighborsMap) 
        distancesMap[pair.first] = -1;

    // On par du sommet de depart, avec une distance de 0
    verticesToProcess.push(startVertex);
    distancesMap[startVertex] = 0;

    // Tant qu'il reste des sommets a traiter
    while (!verticesToProcess.empty()) 
    {
        // Sommet a traiter
        int currentVertex = verticesToProcess.front();
        // Le sommet est retire de la file d'attente
        verticesToProcess.pop();

        // Parcours les voisins du sommet en cours de traitement
        //  et calcul de la distance pour chaque voisin si besoin
        for (int neighbor : d_neighborsMap[currentVertex])
        {
            if (distancesMap[neighbor] == -1) // Si distance pas deja calculee
            {
                // Calcul de la distance du voisin a partir de celle du sommet courant
                distancesMap[neighbor] = distancesMap[currentVertex] + 1;

                // Ajout du voisin dans la file des sommets a traiter
                verticesToProcess.push(neighbor);

                // Si on a atteint le sommet de fin
                if (neighbor == endVertex)
                    break;  // BREAK
            }
        }
    }

    // Distance entre les 2 sommets
    return distancesMap[endVertex];
}

/**
 * Renvoie le diametre du graphe, cad la distance entre
 * les 2 sommets les plus eloignes
 * 
 * Complexite : O(nbSommets^2 x (nbSommets + nbAretes))
*/
void Graph::calculateDiameter()
{
    int maxDiameter = 0;    // Distance maximale trouvee

    // Parcours de toutes les paires de sommets
    for (const auto& pair1 : d_neighborsMap) 
    {
        for (const auto& pair2 : d_neighborsMap) 
        {
            if (pair1.first != pair2.first) // Si les 2 sommets sont differents
            {
                // Calcul de la distance entre les 2 sommets
                int currentDistance = calculateDistance(pair1.first, pair2.first);

                // Mise a jour de la distance max si on en trouve une plus grande
                if (currentDistance > maxDiameter)
                    maxDiameter = currentDistance;
            }
        }
    }
    d_diameter = maxDiameter;
}

/**
 * @return La distance maximale possible entre 2 sommets
*/
int Graph::getDiameter()
{
    return d_diameter;
}

/**
 * @brief Marque une arete comme verifiee
 * @param vertex1
 * @param vertex2
*/
void Graph::markEdgeAsChecked(const int& vertex1, const int& vertex2)
{
    d_checkedEdges.insert({ vertex1, vertex2 });
    d_checkedEdges.insert({ vertex2, vertex1 });
}

/**
 * @return true si la fusion entre les 2 sommets a deja ete verifiee
*/
bool Graph::isEdgeAlreadyChecked(const int& vertex1, const int& vertex2)
{
    // Pas besoin de tester les 2 sens
    pair<int, int> edge = { vertex1, vertex2 };
    if (d_checkedEdges.find(edge) != d_checkedEdges.end())
    {
        return true;
    }
    return false;
}


// OPERATEUR

std::ostream& operator<<(std::ostream& os, const Graph& p)
{
    os << "Graphe : " << endl;
    for (const auto& pair : p.d_neighborsMap)
    {
        os << "Sommet " << pair.first << endl;
        os << "\t Voisins : ";
        string neighborsList = "";
        for (const int& i : pair.second)
        {
            neighborsList += to_string(i) + ", ";
        }
        // Pour ne pas afficher la derniere virgule
        if (!neighborsList.empty()) 
        {
            neighborsList.pop_back();  // Supprime l'espace
            neighborsList.pop_back();  // Supprime la virgule
        }
        os << neighborsList << endl;
    }

    os << endl << "Fusions : " << endl;
    for (const auto& pair : p.d_edgeWeights) {
        os << "Fusion (" << pair.first.first << ", " << pair.first.second << ") : ";
        os << pair.second.getId() << endl;
    }
    return os;
}
