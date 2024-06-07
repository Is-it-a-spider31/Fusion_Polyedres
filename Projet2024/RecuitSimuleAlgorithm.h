#pragma once
#include "Algorithm.h"

#include <random>   // Pour std::default_random_engine et std::uniform_int_distribution

/**
 * @brief Algorithme du recuit simule (ou SA: similated annealing)
*/
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
     * @brief Algorithme principal du recuit simule
    */
    void run() override;

    /**
     * Chemin du repertoire ves lequel l'agoritme ecrit
     * les solutions trouvees sous forme de fichiers .obj
    */
    const string getFilePath() override;

protected:
    /**
     * @brief Affiche le graphique qui montre l'evolution des donnees de l'algo
     */
    void printDataChart(const string& info);

    /**
     * Chemin du repertoire ves lequel l'agoritme ecrit
     * les solutions trouvees sous forme de fichiers .obj
    */
    static const string GENERATE_OBJ_PATH;

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
     * @brief Permute N > 1 elements dans la liste
     *
     * @param polyhedra Liste de polyedres a permuter
     * @param n nombre d'elements a permuter
    */
    void permuteNElements(vector<Polyedre>& polyhedra, const size_t n);

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
    bool isNeighborAccepted(const double& currentEval, const double& neighborEval);

};
