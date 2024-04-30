#include "Plane.h"

Plane::Plane(const Vertex& p1, const Vertex& p2, const Vertex& p3)
{
	// On créé 2 vecteurs à partir des 3 points
	Vertex u = maths::vectorAB(p1, p2);
	Vertex v = maths::vectorAB(p1, p3);

	// Calcul des coefficients du vecteur normal au plan (cross product)
	d_a = u.getY() * v.getZ() - u.getZ() * v.getY();
	d_b = u.getZ() * v.getX() - u.getX() * v.getZ();
	d_c = u.getX() * v.getY() - u.getY() * v.getX();
	// Vertex N = Vertex(-1, d_a, d_b, d_c); //vecteur normal au plan

	// Calcul du coefficient d : ax + by + cz = d
	d_d = d_a * p1.getX() + d_b * p1.getY() + d_c * p1.getZ();

	//std::cout << "d_a :" << d_a << " d_b :" << d_b << " d_c :" << d_c << " d_d : " << d_d << std::endl;
}

Plane::~Plane()
{
}

double Plane::pointPositionFromPlane(const Vertex& p) {
	double result = (d_a * p.getX()) + (d_b * p.getY()) + (d_c * p.getZ()) - d_d;

	// Élimine les imprécisions de calcul
	if (result > -50.0 && result < 50.0) {
		result = 0;
	}

	return result; //positif, nul (sur le plan) ou négatif
}