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
	 * @brief Fusionne le polyedre courant avec un autre polyedre
	 * 
	 * @param otherPoly Autre polyedre avec lequel on veut fusionner
	 * @param sharedFaces Faces communes aux 2 polyedres
	*/
	void mergeWith(const Polyedre otherPoly, const vector<Face> sharedFaces);


	bool isConvex() const;
	void computeConvexity();

	// GETTER
	int getId() const;
	vector<Face> getFaces() const;

	// OPERATEURS 
	// todo surcharger les operateurs, plus tard

	//ECRITURE
	friend std::ostream& operator<<(std::ostream& os, const Polyedre& p);

private:
	/**
	 * @brief Identifiant unique du polyedre
	*/
	int d_id;

	/**
	 * @brief Etat convexe / non convexe du polyèdre
	*/
	bool d_isConvex;
};

