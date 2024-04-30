#include "Polyhedron.h"
#include "Program.h"

// Constructeurs
Polyhedron::Polyhedron(int id) : d_id(id) {}

Polyhedron::~Polyhedron() {}


// Getters
int Polyhedron::getId() const { return d_id; }

int Polyhedron::getFaceId(int i) const { return d_faces[i]; }

std::deque<int> Polyhedron::getFaces() const { return d_faces; }


// Modification de données
void Polyhedron::addFace(int f) {
	d_faces.push_back(f);
}

void Polyhedron::deleteFace(int n) {
	int i = 0;
	while (d_faces[i] != n) {
		++i;
	}
	d_faces.erase(d_faces.begin() + i);
}

void Polyhedron::setId(int id) { d_id = id; }

//Opérations
std::vector<int> Polyhedron::getSharedFaces(const Polyhedron& p) {
	std::vector<int> shared_faces;

	for (int i = 0; i < d_faces.size(); ++i) {
		for (int j = 0; j < p.getFaces().size(); ++j) {
			if (Program::getFace(d_faces[i]) == Program::getFace(p.getFaceId(j))) {
				shared_faces.push_back(d_faces[i]);
			}
		}
	}

	return shared_faces;
}

bool Polyhedron::isConvex() const
{
	for (unsigned int i = 0; i < d_faces.size(); ++i) {
		Plane p(Program::getFace(d_faces[i]).getVertex(0), Program::getFace(d_faces[i]).getVertex(1), Program::getFace(d_faces[i]).getVertex(2));

		// Valeur de référence : tous les points devrons être du même signe que cette valeur. La boucle sert à trouver une valeur de référence non nulle
		unsigned int l = 0, m = 0;
		while (p.pointPositionFromPlane(Program::getFace(d_faces[(i + (l + 1)) % d_faces.size()]).getVertex(m)) == 0.0) {
			if (++m == Program::getFace(d_faces[(i + (l + 1)) % d_faces.size()]).getVertices().size()) {
				m = 0;
				++l;
			}
		}

		bool reference = p.pointPositionFromPlane(Program::getFace(d_faces[(i + (l + 1)) % d_faces.size()]).getVertex(m)) > 0.0;

		for (unsigned int j = i + 1; j < d_faces.size(); ++j) {
			for (unsigned int k = 0; k < Program::getFace(d_faces[j]).getVertices().size(); ++k) {
				double test = p.pointPositionFromPlane(Program::getFace(d_faces[j]).getVertex(k));
				if (((test > 0.0) != reference) && (test != 0.0)) {
					return false;
				}
			}
		}
	}

	return true;
}

std::ostream& operator<<(std::ostream &os, const Polyhedron& p) {
	os << "g Object" << p.d_id << std::endl;
	for (int i = 0; i < p.d_faces.size(); i++) {
		os << Program::getFace(p.d_faces[i]);
	}
	os << std::endl;
	return os;
}
