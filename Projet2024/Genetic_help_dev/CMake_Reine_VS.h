#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;


class geneticQueenAlgo
{

public:
    geneticQueenAlgo(int maxiteration, int popsize, int dim, double probaCross, double probaMut);

    //retourne la taille de la population
    int popSize();

    //maxIteration si on veut limiter le programme
    int maxIteration();

    //dimension du problème
    int dimension();

    //probabilité de croisement
    double probaCross();

    //probablité de mutation
    double probaMut();

    //initialisation Population sans doublons avec des randoms
    void populationInit();

    //cout de l'individu numéro N
    int individuEvaluate(int n);

    //renvoie le gagnant du tournoi
    int turnamentWinner(int x, int y);
    
    //Affiche la population actuelle
    void coutPop();
   
    //affiche l'individu N
    void bestIndiv(int n);

    //copie dans le vector en parametre la population
    vector<vector<int>> d_populationCopy(vector<vector<int>>& tab);
    
    //Croise la moitié des genes du winner avec celui du loser
    void crossover(int winner, int loser);

    //Mute un gène d'une position rdm avec une valeur rdm
    void mutation(int indiv);

    //trie par cout les individue 
    void trie();

    //Change la l'individu ind en position pos dans la population
    void popChange(vector<int> ind, int pos);


private:
    int d_popSize;
    int d_dimension;
    double d_crossoverProbability;
    double d_mutationProbability;
    int d_maxIterations;
    
    vector<vector<int>> d_population;
};


geneticQueenAlgo::geneticQueenAlgo(int maxiteration, int popsize, int dim, double probaCross, double probaMut)
    :d_maxIterations{ maxiteration }, d_popSize{ popsize }, d_dimension{ dim }, d_crossoverProbability{ probaCross }, d_mutationProbability{ probaMut }
{}

int geneticQueenAlgo::popSize() { return d_popSize; }
int geneticQueenAlgo::maxIteration() { return d_maxIterations; }
int geneticQueenAlgo::dimension() { return d_dimension; }
double geneticQueenAlgo::probaCross() { return d_crossoverProbability; }
double geneticQueenAlgo::probaMut() { return d_mutationProbability; }

void geneticQueenAlgo::populationInit()
{
    for (int i = 0; i < d_popSize; i++)
    {
        vector<int> shuffle;
        for (int i = 0; i < d_dimension; i++)
        {
            shuffle.push_back(i);
        }
        int vrandom;

        for (int j = 0; j < d_dimension; j++)
        {
            random_shuffle(shuffle.begin(), shuffle.end());        
        }

        d_population.push_back(shuffle);
    }
}


int geneticQueenAlgo::individuEvaluate(int n)
{
    int conflit = 0;
    for (int i = 0; i < d_dimension - 1; i++)
    {
        for (int j = 1; j < d_dimension; j++)
        {
            if ((abs(i - j) == abs(d_population[n][i] - d_population[n][j])) && (d_population[n][i] != d_population[n][j]))
            {

                conflit++;
            }
        }
    }
    return conflit;
}

void geneticQueenAlgo::coutPop()
{
    cout << endl;
    for (int i = 0; i < d_popSize; i++)
    {
        for (int j = 0; j < d_dimension; j++)
        {
            cout << d_population[i][j] << " ";
        }

        cout << "     " << i << "     cost: " << individuEvaluate(i) << endl;
    }
}



void geneticQueenAlgo::bestIndiv(int n)
{
    cout << "[ ";
    for (int i = 0; i < d_dimension; i++)
    {
        cout << " " << d_population[n][i] << " ";
    }
    cout << " ]";
}




vector<vector<int>> geneticQueenAlgo::d_populationCopy(vector<vector<int>>& tab)
{
    tab = d_population;
    /*for(int i=0; i <d_popSize;i++)
    cout << tab[i] << " ."*/
    return tab;
}



void geneticQueenAlgo::crossover(int winner, int loser) {
    for (int k = 0; k < d_dimension / 2; k++)
    {

        int tmpW = d_population[winner][k];
        int tmpL = d_population[loser][k];


        for (int l = 0; l < d_dimension; l++)
        {
            if (d_population[winner][l] == tmpL)
            {
                d_population[winner][l] = tmpW;
                d_population[winner][k] = tmpL;
            }

            if (d_population[loser][l] == tmpW)
            {
                d_population[loser][l] = tmpL;
                d_population[loser][k] = tmpW;
            }
            
        }
    }

}

void geneticQueenAlgo::mutation(int indiv)
{


    int rdm_pos = rand() % d_dimension / 2 + 1;
    int rdm_value = rand() % d_dimension / 2 + 1;


    for (int l = 0; l < d_dimension; l++)
    {
        if (d_population[indiv][l] == rdm_value)
        {
            d_population[indiv][l] = d_population[indiv][rdm_pos];
            d_population[indiv][rdm_pos] = rdm_value;
        }

    }

}


void geneticQueenAlgo::trie()
{
    vector<vector<int>> cost;
    for (int k = 0; k < popSize(); k++)
    {
        vector<int> ind;
        int cout = individuEvaluate(k);
        ind.push_back(cout);
        ind.push_back(k);
        cost.push_back(ind);
    }
    sort(cost.begin(), cost.end());

    vector<vector<int>> triePop;

    for (int k = 0; k < d_popSize; k++)
    {
        triePop.push_back(d_population[cost[k][1]]);
    }

    d_population = triePop;
}

void geneticQueenAlgo::popChange(vector<int> best, int pos)
{
    d_population[pos] = best;
}



