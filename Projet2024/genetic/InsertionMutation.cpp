#include "InsertionMutation.h"

#include <cstdlib> // Pour srand et rand

/**
 * @brief Mutation d'un individu par insertion
 * 
 * @param individual Individu dont un gene doit muter
*/
void InsertionMutation::mutate(vector<int> individual)
{
    int min = 0;
    int max = individual.size()-1;
    std::srand(42);

    // Selection aleatoire du gene a deplacer
    int selectedGeneIndex = min + std::rand() % (max - min + 1);    // nb aleatoires entre [0, size-1]
    int selectedGene = individual[selectedGeneIndex];

    // Suppression du gene
    individual.erase(individual.begin() + selectedGeneIndex);

    // Nouvelle position a laquelle il faut inserer le gene
    max--;
    int indexToMove = min + std::rand() % (max - min + 1);
    while (selectedGeneIndex == indexToMove)
        indexToMove = min + std::rand() % (max - min + 1);
    
    // Insertion du gene a un autre index que celui de base
    individual.insert(individual.begin() + indexToMove, selectedGene);
}
