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

	/**
	* @brief �num�ration des diff�rentes cha�nes de caract�res reconnues dans un fichier OBJ.
	*
	* Cette �num�ration d�finit les diff�rentes cha�nes de caract�res possibles
	* pour le premier mot d'une ligne dans un fichier OBJ, ce qui permet de d�terminer
	* le type de donn�es que repr�sente la ligne.
	*/
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

	/**
	* @brief R�sout la cha�ne de caract�res en une valeur de l'�num�ration FirstString.
	*
	* Cette fonction prend en entr�e une cha�ne de caract�res et retourne la valeur correspondante
	* de l'�num�ration FirstString. Si la cha�ne de caract�res ne correspond � aucune valeur connue,
	* la fonction retourne dont_know_string.
	*
	* @param input La cha�ne de caract�res � r�soudre.
	* @return La valeur de l'�num�ration FirstString correspondant � la cha�ne de caract�res.
	*/
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

