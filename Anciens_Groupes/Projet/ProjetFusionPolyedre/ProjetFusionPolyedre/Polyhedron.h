#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include "Face.h"
#include "Plane.h"

// Polyèdre constitué de Faces
class Polyhedron
{
public:
	// Constructeurs
	Polyhedron(int id);
	~Polyhedron();

	// Getters
	int getId() const;
	int getFaceId(int i) const;
	std::deque<int> getFaces() const;

	// Modification de données
	void addFace(int f);
	void deleteFace(int i);
	void setId(int id);

	//Opérations
	std::vector<int> getSharedFaces(const Polyhedron& p);
	bool isMergeable(const Face& f) const;
	bool isConvex() const;

	// Entrées - Sorties
	friend std::istream operator>>(std::istream is, Polyhedron& p);
	friend std::ostream& operator<<(std::ostream &os, const Polyhedron& p);

private:
	int d_id; // Identifiant du polyèdre
	std::deque<int> d_faces; // Tableau de faces
};

#endif

