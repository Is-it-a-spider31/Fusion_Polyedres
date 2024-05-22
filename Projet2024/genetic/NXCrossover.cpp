#include "NXCrossover.h"

#include <algorithm>    // Pour std::sort et std::find
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
 * Effectue le croisement des 2 parent et modifie
 * les enfants en parametres en consequence
 *
 * @param parent1
 * @param parent2
 * @param child1 Enfant vide qui sera modifie
 * @param child2 Enfant vide qui sera modifie
*/
void NXCrossover::cross(
	const vector<int>& parent1, 
	const vector<int>& parent2, 
	vector<int>& child1,
	vector<int>& child2
){
    int size = parent1.size();
    // Il faut moins de points de croisement que de genes
    if (size <= d_nbCrossoverPoints)
        return;

    // Liste des points de croisement
    vector<int> crossoverPoints = chooseCrossoverPoints(size);

    // Calcul des 2 enfants (attention a l'ordre des parametres)
    crossOneChild(parent1, parent2, child1, crossoverPoints);
    crossOneChild(parent2, parent1, child2, crossoverPoints);
}

/**
 * @brief Permet de tester le fonctionnement de la classe
*/
void NXCrossover::test()
{
    vector<int> parent1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<int> parent2 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    vector<int> child1, child2;
    d_nbCrossoverPoints = 1; // Nombre de points de croisement
    cross(parent1, parent2, child1, child2);

    /*  TEST DE LA FONCTION FIND
    //            0  1  2  3  4  5     6  7     8     9
    //Parent 1 : [1, 2, 3, 4, 5, 6] | [7, 8] | [9] | [10]
    auto it = std::find(
        parent1.begin() + 9,    // Indice de debut
        parent1.begin() + 10,        // Indice de fin
        10      // Element a chercher
    );
    if (it == parent1.end())
        cout << "Pas trouve ..." << endl;
    else    
        cout << "Trouve !" << endl;
    cout << "it = " << *it << endl;
    */

    // Affichage des resultats
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

/**
 * @brief Selection aleatoire des points de croisement
 * 
 * Le nombre de points de croisements depend 
 * de l'attribut @ref NXCrossover::d_nbCrossoverPoints d_nbCrossoverPoints.
 * Ils sont dans l'interval [1, size-1]
 * 
 * @param size Taille d'un individu
 * @return La liste des points de croisements slectionnes
*/
vector<int> NXCrossover::chooseCrossoverPoints(const int& size)
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
    std::sort(crossoverPoints.begin(), crossoverPoints.end());

    return crossoverPoints;
}

/**
 * @brief Calcul un enfant en croisant 2 parents (croisement N points)
 * 
 * Attention, l'ordre des parents en parametres a son importance.
 * 
 * @param parent1 Parent de reference pour le calcul du croisement
 * @param parent2 Parent qui va servir a modifier les genes de l'enfant
 * @param child Enfant dont les genes de base sont ceux du parent1
 * @param crossoverPoints Liste des points de croisement
*/
void NXCrossover::crossOneChild(
    const vector<int>& parent1,
    const vector<int>& parent2,
    vector<int>& child,
    vector<int> crossoverPoints
)
{
    // Initialisation de l'enfant avec les genes du parent1
    child = parent1;

    // Ajout de l'indice de fin de la liste, pour la fonction std::find
    crossoverPoints.push_back(parent1.size());

    bool swap = true;   // Si vrai, interval a croiser
    int borneInf = crossoverPoints[0];  // 1er point de croisement
    int childIndex = borneInf;  // Indice du gene de l'enfant a modifier

    // Pour chaque points de croisement sauf le premier,
    // cad pour chaque interval de croisement
    for (int i = 1; i <= d_nbCrossoverPoints; i++)
    {
        int borneSup = crossoverPoints[i];  // Point de croisement suivant
        int parent2Index = 0;   // Indice courant pour parcourir le parent2

        // Modification des genes de l'enfant dans l'interval courant
        while (childIndex < borneSup)
        {
            if (swap)
            {   // On est dans un interval dans lequel il faut
                //  modifier les genes de l'enfants

                vector<int>::const_iterator it; // Iterateur
                // Cherche le premier element de parent2 qui est 
                // dans l'interval [borneInf, borneSup[ de parent1
                do 
                {
                   // Attention, avec std::find : interval [borneInf, borneSup[
                    it = std::find(
                        parent1.begin() + borneInf,     // Indice de debut
                        parent1.begin() + borneSup,     // Indice de fin
                        parent2[parent2Index]      // Element a chercher
                    );
                    parent2Index++; // Parcour du parent2 dans l'ordre

                } while (it == parent1.begin() + borneSup);

                // Modification du gene courant de l'enfant
                child[childIndex] = parent2[parent2Index - 1];
            }
            childIndex++;   // Gene suivant
        }
        borneInf = borneSup;
        swap = !swap;   // Croisement d'1 interval sur 2
    }
}
