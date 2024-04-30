#pragma once

#include "Point.h"

/**
 * @brief Classe qui represente un plan
*/
class Plan
{
public:
	
	/**
	 * @brief Construit un plan a partir de 3 points p1 p2 et p3.
	 * 
	 * @param p1
	 * @param p2
	 * @param p3
	*/
	Plan(const Point& p1, const Point& p2, const Point& p3);
	~Plan();

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
	double pointPositionFromPlan(const Point& p);

	/**
	 * @brief Teste si 3 vecteurs u, v et w sont coplanaires
	 * 
	 * @param u 
	 * @param v 
	 * @param w 
	 * @return true si coplanaire, false sinon
	*/
	static bool coplanarVectors(const Point& u, const Point& v, const Point& w);

private:

	// Equation cartesienne du plan
	// ax + by + cz = d
	// avec le vecteur normal : (a, b, c)
	double d_a, d_b, d_c, d_d;

	/**
	 * @brief Renvoie un vecteur a partir de 2 points A et B
	 * 
	 * @param A 
	 * @param B 
	 * @return Le vecteur AB
	*/
	static Point vectorFrom2Points(const Point& A, const Point& B);

};