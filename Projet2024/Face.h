#pragma once


#include "Point.h"
#include <vector>

using namespace std;

/**
 * @brief Classe qui represente une face d'une figure geometrique
*/
class Face
{

public:

	/**
	 * @brief Contructeur a partir des sommets
	 * 
	 * @param sommets sommets de la face
	 * @param id identifiant unique de la face
	*/
	Face(const vector<Point> sommets, int id);

	/**
	 * @brief Sommets de la face
	*/
	vector<Point> d_sommets;

	/**
	 * @brief Teste si la face (polygone) est convexe
	 * @return true si convexe, false sinon
	*/
	bool isConvex() const;

	// GETTERS
	
	/**
	 * @brief renvoie l'identifiant de la face
	 * @return l'id de la face
	*/
	int getId() const;

	/**
	 * @brief renvoie le sommet i
	 * @param i indice du sommet
	 * @return le point correspondant au sommet voulu
	*/
	Point getSommet(int i);

	/**
	* @brief Compare deux objets Face pour l'�galit�.
	*
	* Cet op�rateur v�rifie si deux objets Face sont �gaux.
	*
	* @param f L'objet Face � comparer.
	* @return true si les deux objets Face sont �gaux, false sinon.
	*/
	bool operator==(const Face f) const;


	/**
	* @brief Op�rateur de flux de sortie pour les objets Face.
	*
	* Cette fonction amie permet d'�crire un objet Face dans un flux de sortie.
	* Elle formate les donn�es de l'objet Face pour une sortie lisible.
	*
	* @param os Le flux de sortie dans lequel l'objet Face est �crit.
	* @param f L'objet Face � �crire dans le flux de sortie.
	* @return Une r�f�rence au flux de sortie apr�s l'�criture de l'objet Face.
	*/
	friend std::ostream& operator<<(std::ostream& os, const Face& f);

private:
	/**
	 * @brief Identifiant unique de la face
	*/
	int d_id;

};

