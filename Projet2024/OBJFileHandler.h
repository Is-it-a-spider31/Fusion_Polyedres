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

	enum FirstString {
		commentaire,
		vertex,
		face,
		point,
		vertex_normal,
		vertex_texture,
		line_,
		material,
		usemtl,
		group,
		object,
		smoothgroup,
		dont_know_string,
	};

	static FirstString resolveFirstString(string input);

private:
	/**
	 * @brief Permet d'extraire les donnees d'un sommet dans un tableau
	 *
	 * Format d'une face :
	 * f vertexId/normalId/textureId ...
	 *
	 * Exemple :
	 * f 9/15/7 10/16/7 12/17/7 11/18/7
	 * on veut seulement les vertices :
	 * f 9 10 12 11
	 *
	 * @param str donnees du sommet (vertex, texture, normale) ou vertex niquement
	 * @param delim delimiteur "/", ex : vertex/texture/normale
	 * 
	 * @return tableau des donnees du sommet (en float)
	*/
	static vector<float> vertexDataFromString(const string& str, const char delim);

};

