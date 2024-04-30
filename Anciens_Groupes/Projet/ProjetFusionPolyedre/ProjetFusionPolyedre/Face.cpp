#include "Face.h"


Face::Face(const std::deque<Vertex> vertices, int id) {
	d_vertices.clear();
	d_vertices = vertices;
	d_id = id;
}

Face::~Face() {}


Vertex Face::getVertex(int i) const { return d_vertices[i]; }

std::deque<Vertex> Face::getVertices() const { return d_vertices; }


bool Face::operator==(const Face& f) const {
	if (d_vertices.size() == f.getVertices().size()) {
		int nb_shared_vertices = 0;

		for (int i = 0; i < d_vertices.size(); ++i) {
			for (int j = 0; j < d_vertices.size(); ++j) {
				if (d_vertices[i] == f.getVertex(j)) {
					nb_shared_vertices++;
				}
			}
		}

		return nb_shared_vertices == d_vertices.size();
	}
	return false;
}

bool Face::areCoplanar(const Face& f) const {
	//Vecteurs u et v à partir de 3 points de la face courante
	Vertex u = maths::vectorAB(d_vertices[1], d_vertices[0]);
	Vertex v = maths::vectorAB(d_vertices[2], d_vertices[1]);
	//Vecteurs w1 et w2 à partir de 3 points de la face f
	Vertex w1 = maths::vectorAB(f.d_vertices[1], f.d_vertices[0]);
	Vertex w2 = maths::vectorAB(f.d_vertices[1], f.d_vertices[2]);

	//Coplanarité des vecteurs 3 à 3
	//u = alpha.v + beta.w1 et u = alpha.v + beta.w2
	return (maths::coplanarVectors(u, v, w1) && maths::coplanarVectors(u, v, w2));
}

std::ostream& operator<<(std::ostream& os, const Face& f) {
	os << "f ";
	for (int i = 0; i < f.d_vertices.size(); i++) {
		os << f.d_vertices[i].getId() << " ";
	}
	os << std::endl;

	return os;
}
