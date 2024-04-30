

#include "Plan.h"


Point vectorAB(const Point& A, const Point& B) {
		return Point(-1, B.getX() - A.getX(), B.getY() - A.getY(), B.getZ() - A.getZ());
	}


	bool coplanarVectors(const Point& u, const Point& v, const Point& w) {
		double alpha, beta;
		alpha = (u.getX() - u.getY() / w.getY()) / (v.getX() - v.getY() / w.getY());
		beta = (u.getY() - alpha * v.getY()) / w.getY();

			return u.getZ() == alpha * v.getZ() + beta * w.getZ();
	}



Plan::Plan(const Point& p1, const Point& p2, const Point& p3)
{
	// On créé 2 vecteurs à partir des 3 points
	Point u = vectorAB(p1, p2);
	Point v = vectorAB(p1, p3);

	// Calcul des coefficients du vecteur normal au plan (cross product)
	d_a = u.getY() * v.getZ() - u.getZ() * v.getY();
	d_b = u.getZ() * v.getX() - u.getX() * v.getZ();
	d_c = u.getX() * v.getY() - u.getY() * v.getX();
	// Point N = Point(-1, d_a, d_b, d_c); //vecteur normal au plan

	// Calcul du coefficient d : ax + by + cz = d
	d_d = d_a * p1.getX() + d_b * p1.getY() + d_c * p1.getZ();

	//std::cout << "d_a :" << d_a << " d_b :" << d_b << " d_c :" << d_c << " d_d : " << d_d << std::endl;
}

Plan::~Plan()
{
}

double Plan::pointPositionFromPlan(const Point& p) {
	double result = (d_a * p.getX()) + (d_b * p.getY()) + (d_c * p.getZ()) - d_d;




	return result; //positif, nul (sur le plan) ou négatif
}
