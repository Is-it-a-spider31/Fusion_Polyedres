#pragma once

#include <vector>
#include <string>

#include "Point.h"
#include "Polyedre.h"

using namespace std;

/**
 * Classe utilitaire qui prend en charge la lecture
 * et l'ecriture de fichiers .obj
*/
class OBJFileHandler
{

public:
	/**
	 * @brief Ecriture de polyedres dans un fichier obj
	 * 
	 * @param vertices Liste des sommets
	 * @param polyhedrons Liste des polyedres
	 * @param filename Nom du fichier
	*/
	static void writeOBJ(
		const vector<Point>& vertices,
		const vector<Polyedre>& polyhedrons, 
		const string& filename
	);

	/**
	 * @brief Lecture des donnees depuis un fichier .obj
	 * 
	 * @param vertices Liste des sommets
	 * @param faces Liste des faces
	 * @param polyhedrons Liste des polyedres 
	 * @param filename Nom du fichier 
	*/
	static void loadOBJ(
		vector<Point>& vertices, 
		vector<Face>& faces, 
		vector<Polyedre>& polyhedrons, 
		const string& filename
	);

private:

	static void decouper(const string& str, const char delim, vector<string>& out);
};

