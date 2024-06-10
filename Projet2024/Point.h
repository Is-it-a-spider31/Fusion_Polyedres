#pragma once
#include <iostream>

/**
 * @brief Classe qui represente un point (2D ou 3D)
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
	 * sont dans le m�me sens.
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

	/**
	 * @brief Renvoie l'identifiant du point.
	 * @return L'identifiant du point.
	 */
	int getId() const;

	/**
	 * @brief Renvoie la coordonn�e X du point.
	 * @return La coordonn�e X du point.
	 */
	double getX() const;

	/**
	 * @brief Renvoie la coordonn�e Y du point.
	 * @return La coordonn�e Y du point.
	 */
	double getY() const;

	/**
	 * @brief Renvoie la coordonn�e Z du point.
	 * @return La coordonn�e Z du point.
	 */
	double getZ() const;

	/**
	 * @brief D�finit l'identifiant du point.
	 * @param id L'identifiant � attribuer � l'objet.
	 */
	void setId(int id);

	/**
	 * @brief D�finit la coordonn�e X du point.
	 * @param x La nouvelle valeur de la coordonn�e X.
	 */
	void setX(double x);

	/**
	 * @brief D�finit la coordonn�e Y du point.
	 * @param y La nouvelle valeur de la coordonn�e Y.
	 */
	void setY(double y);

	/**
	 * @brief D�finit la coordonn�e Z du point.
	 * @param z La nouvelle valeur de la coordonn�e Z.
	 */
	void setZ(double z);


	/**
	 * @brief Remplace le point par un nouveau
	 * 
	 * @param v nouveau point
	*/
	void setPoint(const Point& v);

	
	/**
 * @brief Compare deux objets Point pour l'�galit�.
 *
 * Cette m�thode v�rifie si deux objets Point sont �gaux.
 *
 * @param v L'objet Point � comparer.
 * @return true si les deux objets Point sont �gaux, false sinon.
 */
	bool operator==(const Point& v) const;

	/**
	 * @brief Compare deux objets Point pour l'in�galit�.
	 *
	 * Cette m�thode v�rifie si deux objets Point sont diff�rents.
	 *
	 * @param v L'objet Point � comparer.
	 * @return true si les deux objets Point sont diff�rents, false sinon.
	 */
	bool operator!=(const Point& v) const;

	/**
	 * @brief Soustraction de deux objets Point.
	 *
	 * Cette m�thode retourne la diff�rence entre deux objets Point.
	 *
	 * @param v L'objet Point � soustraire.
	 * @return Un nouvel objet Point repr�sentant la diff�rence entre les deux Points.
	 */
	Point operator-(const Point& v) const;

	/**
	 * @brief Op�rateur de flux de sortie pour les objets Point.
	 *
	 * Cette fonction amie permet d'�crire un objet Point dans un flux de sortie.
	 *
	 * @param os Le flux de sortie dans lequel l'objet Point est �crit.
	 * @param p L'objet Point � �crire dans le flux de sortie.
	 * @return Une r�f�rence au flux de sortie apr�s l'�criture de l'objet Point.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Point& p);


private:
	/**
	 * @brief Identifiant unique du point
	*/
	int d_id;

	// Coordonnees x, y et z du point
	double d_x, d_y, d_z;

};