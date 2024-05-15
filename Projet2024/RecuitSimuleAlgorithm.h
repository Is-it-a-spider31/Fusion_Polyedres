#pragma once
#include "Algorithm.h"

#include <random>   // Pour std::default_random_engine et std::uniform_int_distribution

class RecuitSimuleAlgorithm : public Algorithm
{
public:
    /**
     * @brief Contructeur a partir d'un fichier .obj
     *
     * @param filename Nom du fichier .obj
    */
    RecuitSimuleAlgorithm(const string& filename);

    /**
     * @brief Algoritme principal du recuit simule
    */
    void run() override;

private:

    /**
     * @brief Facteur de refroidissement h
    */
    double d_coolingFactor;

    /**
     * @brief Temperature
    */
    double d_temperature;

    /**
     * @brief Generateur de nombre aleatoires
    */
    std::mt19937 d_randomGenerator;

    /**
     * @brief Permute 2 elements dans la liste 
     * 
     * @param polyhedra Liste de polyedres a permuter
    */
    void permute2Elements(vector<Polyedre>& polyhedra);

    /**
     * @brief Teste si la solution voisine est acceptee ou pas
     * 
     * Calcule la probabilite d'acceptation de la solution voisine
     * avec la formule classique donne dans l'algo du recuit simule.
     * 
     * @param currentEval Evaluation de la solution courante
     * @param neighborEval Evaluation de la solution voisine
     * 
     * @return true si solution voisine acceptee, false sinon
    */
    bool isNeighborAccepted(const int& currentEval, const int& neighborEval);


