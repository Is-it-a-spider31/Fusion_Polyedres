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

	// OPERATEUR REDEFINI
	bool operator==(const Face f) const;


private:
	/**
	 * @brief Identifiant unique de la face
	*/
	int d_id;

};

