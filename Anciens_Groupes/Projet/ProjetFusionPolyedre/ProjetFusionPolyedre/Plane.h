#ifndef PLANE_H
#define PLANE_H

#include "Vertex.h"
#include "utils.h"

class Plane
{
public:
	Plane(const Vertex& p1, const Vertex& p2, const Vertex& p3);
	~Plane();

	double pointPositionFromPlane(const Vertex& p);

private:
	double d_a, d_b, d_c, d_d; //coefficients de l'équation du plan
};

#endif
