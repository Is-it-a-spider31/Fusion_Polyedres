#pragma once

#include <string>

using namespace std;

/**
 * @brief Arrondi un nombre a n chiffres apres la virgule
 * 
 * @param value Nombre a arrondir
 * @param n Nombre de chiffres a garder apres la virgule
 * @return Le nombre arrondi
*/
double roundToNDigits(double value, const int& n);

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
string doubleToStringRounded(double roundedValue, const int& n);
