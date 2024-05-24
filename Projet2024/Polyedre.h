#pragma once

#include "Face.h"


/**
 * @brief Represente un polyedre
*/
class Polyedre
{

public:

	/**
	* Constructeur par defaut
	*/
	Polyedre();

	/**
	 * @brief Constructeur
	 * 
	 * @param id Identifiant unique
	*/
	Polyedre(int id);
	
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
	 * @brief Fusionne 2 polyedres si possible
	 *
	 * Si la fusion n'est pas possible, retourne un polyedre
	 *	vide avec son id = -1
	 *
	 * @param poly1
	 * @param poly2
	 * @return Le polyedre fusionne (id = -1 si pas possible)
	*/
	static Polyedre merge2Polyhedra(const Polyedre& poly1, const Polyedre& poly2);


	bool isConvex() const;

	/**
	 * @brief Calcul si le polyedre est convexe ou pas
	 *
	 * Pour savoir si un polyedre est convexe, le principe est de verifier
	 * si pour chaque face, tous les sommets sont du meme cote.
	 *
	*/
	void computeConvexity();

	/**
	 * @brief Genere un identifiant unique a partir d'une paire (a,b).
	 * 
	 * a et b sont interchangeables.
	 * 
	 * @param id1 Id d'un polyedre
	 * @param id2 Id d'un autre polyedre
	 * @param min Nombre minimum qui peut etre genere
	 * @return un identifiant unique
	*/
	static int getUniqueIdFrom2Ids(
		const int& id1, 
		const int& id2, 
		const int& min
	);

	// GETTERS
	int getId() const;
	string getMTL() const;
	vector<Face> getFaces() const;

	//SETTERS
	void setMTL(string name);
	void setId(const int id);

	// OPERATEURS
	bool operator<(const Polyedre& poly) const;

	bool operator==(const Polyedre& poly) const;

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

	string d_texture;

	/**
	 * @brief Renvoie les faces communes entre 2 polyedres
	 *
	 * @param poly1
	 * @param poly2
	 * @return la liste des faces communes entre les 2 polyedres
	*/
	static vector<Face> getSharedFaces(const Polyedre& poly1, const Polyedre& poly2);

	/*
	 * @brief Fusionne 2 polyedres adjacents (au moins une face commune).
	 *
	 * Au moins un des deux polyedres doit avoir plus d'une face.
	 *
	 * @param poly1 1er polyedre
	 * @param poly2 2eme polyedre
	 * @param sharedFaces Liste des faces communes aux 2 polyedres
	 *
	 * @return Le polyedre resultant de la fusion
	*/
	static Polyedre merge2AdjacentPolyhedra(const Polyedre& poly1, const Polyedre& poly2, const vector<Face> sharedFaces);

	/**
	 * @brief Fusionne 2 polygones
	 *
	 * Un polygone est un polyedre avec un volume nul
	 * (c'est-a-dire un polyedre avec une seule face)
	 *
	 * @param poly1
	 * @param poly2
	 * @return Le polygone resultant de la fusion (si id=-1, alors fusion pas possible)
	*/
	static Polyedre merge2Polygones(const Polyedre& poly1, const Polyedre& poly2);

};

