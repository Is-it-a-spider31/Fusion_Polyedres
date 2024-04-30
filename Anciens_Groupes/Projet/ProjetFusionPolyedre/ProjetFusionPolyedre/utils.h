#ifndef UTILS_H
#define UTILS_H

#include "Vertex.h"

namespace maths {
	Vertex vectorAB(const Vertex& A, const Vertex& B); //retourne le vecteur AB
	bool coplanarVectors(const Vertex& u, const Vertex& v, const Vertex& w);
}

#endif