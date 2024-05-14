#include "Plan.h"

/**
 * @brief Construit un plan a partir de 3 points p1 p2 et p3.
 *
 * @param p1
 * @param p2
 * @param p3
*/
Plan::Plan(const Point& p1, const Point& p2, const Point& p3)
{
	// Vecteurs directeurs du plan a partir de 3 points
	Point u = vectorFrom2Points(p1, p2);
	Point v = vectorFrom2Points(p1, p3);

	// Calcul de la normale au plan par produits vectoriels
	d_a = u.getY() * v.getZ() - u.getZ() * v.getY();
	d_b = u.getZ() * v.getX() - u.getX() * v.getZ();
	d_c = u.getX() * v.getY() - u.getY() * v.getX();

	// Calcul du coefficient d : ax + by + cz = d
	d_d = d_a * p1.getX() + d_b * p1.getY() + d_c * p1.getZ();

	//std::cout << "d_a :" << d_a << " d_b :" << d_b << " d_c :" << d_c << " d_d : " << d_d << std::endl;
}


/**
 * @brief Test de quel cote est un point par rapport au plan.
 *
 * Renvoie un nombre :
 * > 0 : point a droite du plan
 * < 0 : point a gauche du plan
 * 0 : point sur le plan
 *
 * @param p point a tester
 * @return une valeur qui indique de quel cote est le point
*/
double Plan::pointPositionFromPlan(const Point& p) {
	double result = (d_a * p.getX()) + (d_b * p.getY()) + (d_c * p.getZ()) - d_d;
	return result; //positif, nul (sur le plan) ou n�gatif
}


/**
 * @brief Renvoie un vecteur a partir de 2 points A et B
 *
 * @param A
 * @param B
 * @return Le vecteur AB
*/
Point Plan::vectorFrom2Points(const Point& A, const Point& B) {
	return Point(-1, B.getX() - A.getX(), B.getY() - A.getY(), B.getZ() - A.getZ());
}


bool Plan::coplanarVectors(const Point& u, const Point& v, const Point& w) {
	/*double alpha, beta;
	alpha = (u.getX() - u.getY() / w.getY()) / (v.getX() - v.getY() / w.getY());
	beta = (u.getY() - alpha * v.getY()) / w.getY();

	return u.getZ() == alpha * v.getZ() + beta * w.getZ();*/
	// Calcul du produit scalaire du produit vectoriel de u et v avec w
	double dotProduct = u.crossProduct(v).dotProduct(w);

	// Si le produit scalaire est très proche de zéro (pour prendre en compte les erreurs de précision)
	return std::abs(dotProduct) < 1e-9;
}

Plan::~Plan()
{
}
