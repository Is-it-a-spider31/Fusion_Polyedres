#include "Population.h"
#include <algorithm>
#include <set>

Population::Population(int dimension, int popSize): d_dimension{dimension}, d_popSize{popSize}
{
}


vector<vector<int>> Population::randomInit()
{
    vector<vector<int>> population;
    
    // Utilisé pour éviter les doublons
    set<vector<int>> seen; 

    // Tant que la taille de la population est inférieure à popsize
    while (population.size() < d_popSize) {
        std::vector<int> individual = generateRandomIndiv();
        // Si l'individu n'a pas été vu auparavant
        if (seen.find(individual) == seen.end()) {
            population.push_back(individual);
            seen.insert(individual);
        }
    }
    return population;
}

vector<int> Population::generateRandomIndiv()
{
    vector<int> individual(d_dimension);
    for (int i = 0; i < d_dimension; ++i) {
        individual[i] = i;
    }
    random_shuffle(individual.begin(), individual.end());
    return individual;
}
