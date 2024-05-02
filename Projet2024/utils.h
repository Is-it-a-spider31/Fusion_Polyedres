#pragma once

#include <vector>
#include "Point.h"
#include "Polyedre.h"
#include <string>

/**
 * @brief Ecritue de polyedres dans un fichier obj
 *
 * @param points liste des vertices
 * @param polyedres listes des polyedres
 * @param filename nom du fichier a enregistrer
*/
void writeObjFile(vector<Point> points, vector<Polyedre> polyedres, string fileName);