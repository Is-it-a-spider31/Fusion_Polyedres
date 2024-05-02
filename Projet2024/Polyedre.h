#pragma once

#include "Face.h"

/**
 * @brief Represente un polyedre
*/
class Polyedre
{

public:

	/**
	 * @brief Constructeur par defaut
	 * 
	 * @param id Identifiant unique
	*/
	Polyedre(int id);

	/**
	 * @brief Liste des faces du polyedre
	*/
	vector<Face> faces;

	/**
	 * @brief Renvoie les faces communes entre 2 polyedres
	 * 
	 * @param poly1 
	 * @param poly2 
	 * @return la liste des faces communes entre les 2 polyedres
	*/
	static vector<Face> getSharedFaces(Polyedre& poly1, Polyedre& poly2);

	/**
	 * @brief Fusionne le polyedre avec un autre polyedre
	 * 
	 * @param otherPoly Autre polyedre avec lequel on veut fusionner
	*/
	void mergeWith(const Polyedre otherPoly);


	const bool isConvex();

	// GETTER
	int getId() const;

	// OPERATEURS 
	// todo surcharger les operateurs, plus tard

private:
	/**
	 * @brief Identifiant unique du polyedre
	*/
	int d_id;

	bool d_isConvex;
};

