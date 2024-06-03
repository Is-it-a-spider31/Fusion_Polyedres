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

void ExportAlgoData::displayChart(const string& dataFilePath, const string& dataFileName)
{

    string command = "scripts\\pythonGenerateGraph\\dist\\plot_graph.exe " + dataFilePath + " " + dataFileName;

    cout << "Commande : " << command << endl;
    #ifdef __linux__ // OS Linux
        command = "./scripts/pythonGenerateGraph/dist/plot_graph " + dataFilePath + " " + dataFileName;
    #endif

    // Convertion string en char* pour system()
    char* cstr = new char[command.length() + 1];    // Allocation de la memoire
    strcpy_s(cstr, command.length() + 1, command.c_str());  // Copie

    // Script python qui creer le graphique
    #ifdef _WIN32 // OS Windows
        system(cstr);
    #elif __linux__ // OS Linux
        system(cstr);
    #endif
}
