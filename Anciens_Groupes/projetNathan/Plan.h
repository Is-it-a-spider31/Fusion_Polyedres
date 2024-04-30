#ifndef PLANE_H
#define PLANE_H

#include "Point.h"

class Plan
{
public:
	Plan(const Point& p1, const Point& p2, const Point& p3);
	~Plan();

	double pointPositionFromPlan(const Point& p);

	//coefficients de l'équation du plan
	double d_a, d_b, d_c, d_d;
private:

};

#endif
