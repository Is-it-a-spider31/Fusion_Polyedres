#include "Point.h"


/**
 * @brief Constructeur a partir de 3 coordonnees
 *
 * @param id identifiant unique du point
 * @param x coordonnee en x
 * @param y coordonnee en y
 * @param z coordonnee en z
*/
Point::Point(int id, double x, double y, double z) : d_id(id), d_x(x), d_y(y), d_z(z) {}

/**
 * @brief Constructeur par copie
 *
 * @param p Point a copier
*/
Point::Point(const Point& p)
{
	d_id = p.d_id;
	d_x = p.d_x;
	d_y = p.d_y;
	d_z = p.d_z;
}

Point::~Point() {}

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
int Point::are2EdgesEquals(const Point& p1, const Point& p2, const Point& q1, const Point& q2)
{
	int areEquals = 0;	// segements differents par defaut

	// p1-----p2
	// q1-----q2
	if ((p1 == q1 && p2 == q2))
	{
		areEquals = 1;
	}
	// p1-----p2
	// q2-----q1
	else if (p2 == q1 && p1 == q2)
	{
		areEquals = -1;
	}

	return areEquals;
}


/**
 * @brief Produit vectoriel entre 2 vecteurs
 *
 * @param other Autre vecteur
 * @return
*/
Point Point::crossProduct(const Point& other) const
{
	double newX = d_y * other.d_z - d_z * other.d_y;
	double newY = d_z * other.d_x - d_x * other.d_z;
	double newZ = d_x * other.d_y - d_y * other.d_x;
	return Point(0, newX, newY, newZ);
}

double Point::dotProduct(const Point& other) const
{
	return d_x * other.d_x + d_y * other.d_y + d_z * other.d_z;
}


// GETTERS

int Point::getId() const { return d_id; }

double Point::getX() const { return d_x; }

double Point::getY() const { return d_y; }

double Point::getZ() const { return d_z; }


// SETTERS

void Point::setId(int id) { d_id = id; }

void Point::setX(double x) { d_x = x; }

void Point::setY(double y) { d_y = y; }

void Point::setZ(double z) { d_z = z; }

/**
 * @brief Remplace le point par un nouveau
 *
 * @param v nouveau point
*/
void Point::setPoint(const Point& v) {
	d_id = v.d_id;
	d_x = v.d_x;
	d_y = v.d_y;
	d_z = v.d_z;
}

// OPERATEUR REDEFINIS

bool Point::operator==(const Point& v) const
{
	return(d_x == v.d_x && d_y == v.d_y && d_z == v.d_z);
}

bool Point::operator!=(const Point& v) const
{
	return !(*this == v);
}

Point Point::operator-(const Point& v) const
{
	Point res(v);
	res.d_x -= this->d_x;
	res.d_y -= this->d_y;
	res.d_z -= this->d_z;

	return res;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "v " << p.getX() << " " << p.getY() << " " << p.getZ() << std::endl;
	return os;
}
