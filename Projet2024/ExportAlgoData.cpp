#include "ExportAlgoData.h"

#include <iostream>
#include <fstream>  // Pour ecrire dans un fichier

// Pour la date
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

#include <cstdlib> // Pour la fonction system()

#include <windows.h>

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
void ExportAlgoData::writeDataToFile(
    const string& filepath,    // Chemin du fichier
    const string& filename,    // Nom du fichier
    const string& xAxisName,   // Nom de l'axe X
    const string& yAxisName,   // Nom de l'axe Y
    const string& legend,      // Legende
    const string& title,       // Titre du graphique
    const string& infoBox,     // Informations supplementaires
    const bool& invertX        // Axe X dans l'ordre decroissant
)
{
    const string fullPath = filepath + filename + ".txt";
    ofstream file(fullPath);

    /*
    cout << "File path : " << fullPath << endl;
    #ifdef _WIN32
        wchar_t cwd[260];
        if (GetCurrentDirectory(260, cwd) != 0) {
            std::wcout << "Repertoire courant : " << cwd << std::endl;
        }
    #endif
    */

    if (file.is_open()) {
        file << "Title: " << title << "\n";
        file << "X-Axis: " << xAxisName << "\n";
        file << "Y-Axis: " << yAxisName << "\n";
        file << "Legend: " << legend << "\n";
        file << "InfoBox: " << infoBox << "\n";
        file << "InvertX: " << invertX << "\n";
        file << "Data:\n";
        for (const Point& point : dataPoints) {
            file << point.getX() << "," << point.getY() << "\n";
        }
        file.close();

        // Affichage du graphique correspondant aux donnees
        displayChart(filepath, filename);
    }
    else {
        cerr << "Unable to open file";
    }
}

/**
 * @brief Ajoute un point 2D au graphique
 *
 * @param x Coordonne X du point
 * @param y Coordonne Y du point
*/
void ExportAlgoData::addPoint(const double x, const double y)
{
    dataPoints.push_back(Point(x, y));
}

/**
 * @return La date courante en chaine de caracteres
*/
string ExportAlgoData::getCurrentDateTime()
{
    // Date courante
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    // Convertion acec le fuseau horaire local
    tm local_tm;
    localtime_s(&local_tm , &now_time);

    // Formatage de la date en une chaine de caracteres
    ostringstream oss;
    oss << put_time(&local_tm, "%Y-%m-%d-%H%M%S");
    return oss.str();
}


/**
 * @brief Affiche un graphique à partir des données fournies en utilisant un executable.
 *
 * Cette fonction prend en entrée le chemin du fichier de données et le nom du fichier de données,
 * puis génère un graphique à partir de ces données en utilisant un executable.
 *
 * @param dataFilePath Le chemin du fichier de données.
 * @param dataFileName Le nom du fichier de données.
 */
void ExportAlgoData::displayChart(const std::string& dataFilePath, const std::string& dataFileName)
{
    // Construction de la commande pour générer le graphique
    std::string command = "scripts\\pythonGenerateGraph\\dist\\plot_graph.exe " + dataFilePath + " " + dataFileName;

    // Affichage de la commande
    std::cout << "Commande : " << command << std::endl;

    // Exécution du script Python pour créer le graphique
#ifdef _WIN32 // Pour les systèmes Windows
    system(command.c_str());
#elif __linux__ // Pour les systèmes Linux
    // Construction de la commande pour Linux
    command = "./scripts/pythonGenerateGraph/dist/plot_graph " + dataFilePath + " " + dataFileName;
    system(command.c_str());
#endif
}

