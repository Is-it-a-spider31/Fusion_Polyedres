#pragma once

#include <vector>
#include <string>

#include "Point.h"

using namespace std;

/**
 * @brief Permet d'exporter les donnees d'un algorithme dans un fichier.
 * Ce fichier pourra ensuite etre utilise pour afficher un graphique.
 * Exemple : evolution de l'objectif en fonction nombre d'iteration
 *
*/
class ExportAlgoData
{

public:
    /**
     * Genere un fichier qui stocke les informations utiles
     * d'une execution de l'algo pour afficher un graphique.
     * Exemple : evolution de l'objectif en fonction nombre d'iteration
     *
     * @param filename Nom du fichier
     * @param xAxisName Nom de l'axe X
     * @param yAxisName Nom de l'axe Y
     * @param legend Legende
     * @param title Titre du graphique
     * @param infoBox Informations supplementaires
     * @param invertX Si vrai, valeurs sur l'axes par ordre decroissant
    */
    void writeDataToFile(
        const string& filepath,
        const string& filename,    // Nom du fichier
        const string& xAxisName,   // Nom de l'axe X
        const string& yAxisName,   // Nom de l'axe Y
        const string& legend,      // Legende
        const string& title,       // Titre du graphique
        const string& infoBox,     // Informations supplementaires
        const bool& invertX        // Axe X dans l'ordre decroissant
    );

    /**
     * @brief Ajoute un point 2D au graphique
     *
     * @param x Coordonne X du point
     * @param y Coordonne Y du point
    */
    void addPoint(const double x, const double y);

    /**
     * @return La date courante en chaine de caracteres
    */
    string getCurrentDateTime();

private:
    /**
     * @brief Points qui constituent le graphe
    */
    vector<Point> dataPoints;

    /**
 * @brief Affiche un graphique � partir des donn�es fournies en utilisant un executable.
 *
 * Cette fonction prend en entr�e le chemin du fichier de donn�es et le nom du fichier de donn�es,
 * puis g�n�re un graphique � partir de ces donn�es en utilisant un executable.
 *
 * @param dataFilePath Le chemin du fichier de donn�es.
 * @param dataFileName Le nom du fichier de donn�es.
 */
    void displayChart(const string& dataFilePath, const string& dataFileName);
};

