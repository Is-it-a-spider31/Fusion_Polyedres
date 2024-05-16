#include "GeneticAlgorithm.h"



GeneticAlgorithm::GeneticAlgorithm(const string& filename, int popSize, double probaCross, double probaMut, int maxIter): 
	Algorithm(filename), d_popSize{popSize}, d_crossoverProba{probaCross}, d_mutationProba{probaMut}
{

}

void GeneticAlgorithm::run()
{

}
