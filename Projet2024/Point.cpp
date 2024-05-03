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

Point::~Point() {}



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
