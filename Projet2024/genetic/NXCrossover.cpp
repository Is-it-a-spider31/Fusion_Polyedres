#include "NXCrossover.h"

#include <algorithm>    // Pour sort
#include <iostream>

/**
 * @brief Constructeur
 *
 * @param nbPoints Nombre de points de croisement
*/
NXCrossover::NXCrossover(int nbPoints) : d_nbCrossoverPoints{nbPoints} {}

/**
 * @brief Croisement en N points de 2 individus
 *
 * @param parent1
 * @param parent2
 * @param child1
 * @param child2
*/
void NXCrossover::cross(
	const vector<int>& parent1, 
	const vector<int>& parent2, 
	vector<int>& child1,
	vector<int>& child2
){
    int size = parent1.size();
    if (size <= d_nbCrossoverPoints)
        return;

    // Liste des points de croisement
    vector<int> crossoverPoints = chooseCrossoverPoints(size);

    cout << "crossover Points: ";
    for (int num : crossoverPoints) {
        cout << num << " ";
    }
    cout << endl;

    child1.resize(size, -1);
    child2.resize(size, -1);
    int old = 0;
    
    // EXEMPLE
    //N points : 6 8 9
    //
    //    Parent 1 : [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    //    Parent 2 : [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
    //
    //                0   1  2  3  4  5     6  7     8     9
    //    Parent 1 : [1,  2, 3, 4, 5, 6] | [7, 8] | [9] | [10]
    //    Parent 2 : [10, 9, 8, 7, 6, 5] | [4, 3] | [2] | [1]
    //
    //    Parent 1 : [1,  2, 3, 4, 5, 6] | [-1, -1] | [9] | [-1]
    //    Parent 2 : [10, 9, 8, 7, 6, 5] | [-1, -1] | [2] | [-1]
    child1 = parent1;
    child2 = parent2;

    crossoverPoints.push_back(crossoverPoints[d_nbCrossoverPoints - 1]);
    crossOneChild(parent1, parent2, child1, crossoverPoints);
    crossOneChild(parent2, parent1, child2, crossoverPoints);
}

void NXCrossover::test()
{
    vector<int> parent1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<int> parent2 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    vector<int> child1, child2;
    d_nbCrossoverPoints = 3; // Nombre de points de croisement
    cross(parent1, parent2, child1, child2);

    //                0  1  2  3  4  5     6  7     8     9
    //    Parent 1 : [1, 2, 3, 4, 5, 6] | [7, 8] | [9] | [10]
    //auto it = std::find(
    //    parent1.begin() + 9,    // Indice de debut
    //    parent1.begin() + 9,        // Indice de fin
    //    10      // Element a chercher
    //);

    //if (it == parent1.begin() + 8)
    //    cout << "Pas trouve ..." << endl;
    //else    
    //    cout << "Trouve !" << endl;

    cout << "N : " << d_nbCrossoverPoints << endl;

    cout << "Parent 1: ";
    for (int num : parent1) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Parent 2: ";
    for (int num : parent2) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Enfant 1: ";
    for (int num : child1) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Enfant 2: ";
    for (int num : child2) {
        cout << num << " ";
    }
    cout << endl;

}

vector<int> NXCrossover::chooseCrossoverPoints(int& size)
{
    // Liste des points de croisement
    vector<int> crossoverPoints;

    // Choix aléatoire des N points de croisement
    for (int i = 0; i < d_nbCrossoverPoints; i++) {
        int point;

        // Le points choisis au hasard doivent etre different des precedents
        do {
            point = rand() % (size - 1) +1;    // Choix aleatoire
        } while (find(crossoverPoints.begin(), crossoverPoints.end(), point) != crossoverPoints.end());
        crossoverPoints.push_back(point);
    }

    // Tri de la liste des points dans l'ordre
    sort(crossoverPoints.begin(), crossoverPoints.end());

    return crossoverPoints;
}

void NXCrossover::crossOneChild(
    const vector<int>& parent1,
    const vector<int>& parent2,
    vector<int>& child,
    vector<int> crossoverPoints
)
{
    int size = parent1.size();
    bool swap = false;

    swap = true;
    for (int i = 1; i < d_nbCrossoverPoints; i++)
    {
        int j = crossoverPoints[i - 1];

        int index = 0;
        while (j < crossoverPoints[i])
        {
            if (swap)
            {
                // Cherche le premier element de parent1 qui n'est pas dans child1
                auto it = parent1.begin() + crossoverPoints[i];
                do {
                    it = std::find(
                        parent1.begin() + crossoverPoints[i - 1],    // Indice de debut
                        parent1.begin() + crossoverPoints[i],        // Indice de fin
                        parent2[index]      // Element a chercher
                    );
                    index++;

                } while (it == parent1.begin() + crossoverPoints[i]);
                child[j] = parent2[index - 1];
            }
            j++;
        }
        swap = !swap;
    }

    if (crossoverPoints[d_nbCrossoverPoints - 1] == size - 1) {

        auto it = parent1.end();
        int index = 0;
        do {
            auto it = std::find(
                parent1.begin() + size - 1,    // Indice de debut
                parent1.begin() + size - 1,    // Indice de fin
                parent2[index]      // Element a chercher
            );

            index++;

        } while (it == parent1.begin() + size - 1);
        child[size - 1] = parent2[index - 1];
    }
}
