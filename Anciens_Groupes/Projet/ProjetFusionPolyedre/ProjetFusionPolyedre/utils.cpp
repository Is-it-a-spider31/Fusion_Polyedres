#include "utils.h"

namespace maths {

	Vertex vectorAB(const Vertex& A, const Vertex& B) {
		return Vertex(-1, B.getX() - A.getX(), B.getY() - A.getY(), B.getZ() - A.getZ());
	}


	bool coplanarVectors(const Vertex& u, const Vertex& v, const Vertex& w) {
		double alpha, beta;
		alpha = (u.getX() - u.getY() / w.getY()) / (v.getX() - v.getY() / w.getY());
		beta = (u.getY() - alpha * v.getY()) / w.getY();

			return u.getZ() == alpha * v.getZ() + beta * w.getZ();
	}

}

