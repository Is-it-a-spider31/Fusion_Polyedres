#include "Graph.h"

#include <iostream>
#include <queue>

/**
 * @brief Ajoute un sommet au graphe
 *
 * @param vertex Sommet a ajouter
*/
void Graph::addVertex(int vertex)
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
 * Les 2 sommets devraient deja etre dans le graphe
 *
 * @param vertex1 1er sommet
 * @param vertex2 2eme sommet
*/
void Graph::addEdge(int vertex1, int vertex2)
{
    // Si les sommets existes
    if (d_neighborsMap.find(vertex1) != d_neighborsMap.end()
        && d_neighborsMap.find(vertex2) != d_neighborsMap.end())
    { 
        d_neighborsMap[vertex1].push_back(vertex2);
        d_neighborsMap[vertex2].push_back(vertex1);
    }
    else // Les sommets ne sont pas dans le graphe
    {   
        cerr << "Appelle de Graph::addEdge (" << vertex1 << ", " << vertex2 << ")" << endl;
        cerr << "Un des 2 sommets n'existe pas !" << endl;
    }
}

/**
 * @brief Renvoie la liste des voisins d'un sommet
 *
 * Le sommet devrait deja etre dans le graphe
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
 * Les 2 sommets devraient deja etre dans le graphe
 * Si l'un des deux n'est pas dans le graphe, renvoie -1
 *
 * @param startVertex Sommet de depart
 * @param endVertex Sommet de fin
 * @return La distance entre les 2 sommets (ou -1)
*/
int Graph::calculateDistance(int startVertex, int endVertex)
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
        distancesMap[pair.first] = std::numeric_limits<int>::max();

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
