#include "Graph.h"

#include <iostream>
#include <queue>

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
        d_neighborsMap[vertex] = vector<int>();  // Ajout du sommet
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
    // Ajout des sommets s'ils ne sont pas dans le graphe 
    addVertex(vertex1);
    addVertex(vertex2);

    // Mise a jour des voisins
    d_neighborsMap[vertex1].push_back(vertex2);
    d_neighborsMap[vertex2].push_back(vertex1);

    // Association du polyedre fusionne a l'arete
    d_edgeWeights[{vertex1, vertex2}] = mergedPoly;
    d_edgeWeights[{vertex2, vertex1}] = mergedPoly;
}

/**
 * @brief Renvoie la liste des voisins d'un sommet
 *
 * Le sommet soit deja etre dans le graphe
 * 
 * @param vertex Sommet dont on cherche les voisins
 * @return La liste des voisins
*/
vector<int> Graph::getNeighbors(int vertex)
{
    if (d_neighborsMap.find(vertex) != d_neighborsMap.end())
    {   // Si le sommet existe
        return d_neighborsMap[vertex];
    }
    else
    {   // Le sommet n'est pas dans le graphe
        cerr << "Appelle de Graph::getNeighbors (" << vertex << ")" << endl;
        cerr << "Le sommet " << vertex << "n'existe pas !" << endl;
    }

    return vector<int>();
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
 *
 * @return La distance maximale entre 2 sommets
*/
int Graph::calculateDiameter()
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
    return maxDiameter;
}
