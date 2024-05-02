#include "Algorithm.h"
#include <fstream>
#include "OBJFileHandler.h"

/**
 * @brief Contructeur a partir d'un fichier .obj
 *
 * @param filename Nom du fichier .obj
*/
Algorithm::Algorithm(const string& filename)
{
	// Chargement des donnees a partir du fichier .obj
	OBJFileHandler::loadOBJ(d_vertices, d_faces, d_polyhedrons, filename);
}

void Algorithm::run()
{

}
