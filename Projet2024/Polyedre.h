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
	 * @brief Constructeur par copie
	 * 
	 * @param copy Polyedre a copier
	*/
	Polyedre(const Polyedre& copy);

	/**
	 * @brief Constructeur par copie en excluant des faces
	 * 
	 * @param copy Polyedre a copier
	 * @param sharedFaces Faces a ne pas copier
	*/
	Polyedre(const Polyedre& copy, const vector<Face>& excludedFaces);

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
	static Polyedre merge2Polyhedrons(const Polyedre& poly1, const Polyedre& poly2, const vector<Face> sharedFaces);


	bool isConvex() const;
	void computeConvexity();

	// GETTERS
	int getId() const;
	vector<Face> getFaces() const;

	// OPERATEURS
	bool operator<(const Polyedre& poly) const;

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

