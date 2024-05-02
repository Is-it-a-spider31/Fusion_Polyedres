#pragma once

/**
 * @brief Classe qui represente un point
*/
class Point
{

public:
	/**
	 * @brief Constructeur a partir de 3 coordonnees
	 * 
	 * @param id identifiant unique du point
	 * @param x coordonnee en x
	 * @param y coordonnee en y
	 * @param z coordonnee en z
	*/
	Point(int id, double x, double y, double z);
	~Point();

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
	bool operator==(Point v);
	bool operator!=(Point v);

private:
	/**
	 * @brief Identifiant unique du point
	*/
	int d_id;

	// Coordonnees x, y et z du point
	double d_x, d_y, d_z;

};