#include "myUtils.h"

#include <cmath>
#include <sstream>  // Pour ostringstream
#include <iomanip>  // Pour setprecision()

/**
 * @brief Arrondi un nombre a n chiffres apres la virgule
 *
 * @param value Nombre a arrondir
 * @param n Nombre de chiffres a garder apres la virgule
 * @return Le nombre arrondi
*/
double roundToNDigits(double value, const int& n)
{
    double factor = pow(10.0, n);
    return round(value * factor) / factor;
}

/**
 * @brief Converti un double en string (sans les zeros inutiles).
 *
 * En effet la fonction to_string() classique ajoute des zeros inutiles
 * meme si le nombre (double) est deja arrondi.
 * Exemples :
 *  1.35 -> "1.350000"
 *
 * @param value  Nombre a convertir (deja arrondi)
 * @param n Nombre de chiffres a garder apres la virgule
 * @return Le nombre arrondi en string
*/
string doubleToStringRounded(double value, const int& n)
{
    value = roundToNDigits(value, n);

    ostringstream oss;
    oss << fixed << setprecision(n) << value;
    string str = oss.str();

    // Supprimer les zéros inutiles
    str.erase(str.find_last_not_of('0') + 1, string::npos); // Supprime les zéros à la fin
    if (str.back() == '.') {
        str.pop_back(); // Supprime le point décimal s'il est à la fin
    }

    return str;
}
