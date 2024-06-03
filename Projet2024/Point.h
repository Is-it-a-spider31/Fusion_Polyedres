#pragma once
#include <iostream>

/**
 * @brief Classe qui represente un point
*/
class Point
{

public:

	/**
	 * @brief Constructeur a partir de 2 coordonnees.
	 * La coordonnee en z est ignoree
	 *
	 * @param x coordonnee en x
	 * @param y coordonnee en y
	*/
	Point(double x, double y);

	/**
	 * @brief Constructeur a partir de 3 coordonnees
	 * 
	 * @param id identifiant unique du point
	 * @param x coordonnee en x
	 * @param y coordonnee en y
	 * @param z coordonnee en z
	*/
	Point(int id, double x, double y, double z);

	/**
	 * @brief Constructeur par copie
	 * 
	 * @param p Point a copier
	*/
	Point(const Point& p);
	~Point();

	/**
	 * @brief Teste si 2 arretes sont identiques
	 *
	 * Teste si les segments [p1, p2] et [q1, q2]
	 * sont identiques et si les points des 2 arretes
	 * sont dans le même sens.
	 *
	 * Retours :
	 * 1 : [p1, p2] = [q1, q2]
	 * -1 : [p1, p2] = [q2, q1]
	 * 0 : arretes differentes
	 *
	 * @param p1 Point du 1er segment
	 * @param p2 Point du 1er segment
	 * @param q1 Point du 2eme segment
	 * @param q2 Point du 2eme segment
	 *
	 * @return 1 ou -1 si les arretes sont identiques, 0 sinon
	*/
	static int are2EdgesEquals(const Point& p1, const Point& p2, const Point& q1, const Point& q2);

	/**
	 * @brief Produit vectoriel entre 2 vecteurs
	 * 
	 * @param other Autre vecteur
	 * @return 
	*/
	Point crossProduct(const Point& other) const;

	/**
	 * @brief Produit scalaire
	 * @param other 
	 * @return 
	*/
	double dotProduct(const Point& other) const;

	// GETTERS
	int getId() const;
	double getX() const;
	double getY() const;
	double getZ() const;

	// SETTERS
	void setId(int id);
	void setX(double x);
	void setY(double y);
	void setZ(double z);

	/**
	 * @brief Remplace le point par un nouveau
	 * 
	 * @param v nouveau point
	*/
	void setPoint(const Point& v);

	// OPERATEURS REDEFINIS
	bool operator==(const Point& v) const;
	bool operator!=(const Point& v) const;
	Point operator-(const Point& v) const;

	friend std::ostream& operator<<(std::ostream& os, const Point& );

private:
	/**
	 * @brief Identifiant unique du point
	*/
	int d_id;

	// Coordonnees x, y et z du point
	double d_x, d_y, d_z;

};