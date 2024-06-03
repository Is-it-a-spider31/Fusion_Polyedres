#pragma once

#include "RecuitSimuleAlgorithm.h"

class RecuitSimuleProf : public RecuitSimuleAlgorithm
{

public:
    /**
     * @brief Contructeur a partir d'un fichier .obj
     *
     * @param filename Nom du fichier .obj
    */
    RecuitSimuleProf(const string& filename);


    /**
     * @brief Algorithme principal du recuit simule
    */
    void run() override;

private:
    /**
     * @brief Teste si la solution voisine est acceptee ou pas.
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

    /**
     * @brief Affiche le graphique qui montre l'evolution des donnees de l'algo
     */
    void printDataChart(const string& info);

    /**
     * Chemin du repertoire ves lequel l'agoritme ecrit
     * les solutions trouvees sous forme de fichiers .obj
    */
    static const string GENERATE_OBJ_PATH;

};

