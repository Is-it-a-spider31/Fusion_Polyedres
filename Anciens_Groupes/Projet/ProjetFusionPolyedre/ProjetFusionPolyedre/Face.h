#ifndef FACE_H
#define FACE_H

#include "Vertex.h"
#include "utils.h"
#include <deque>

//Face d'un objet, constituée de Vertex
class Face
{
public:
	Face(const std::deque<Vertex>, int id);
	~Face();

	//Getters
	Vertex getVertex(int i) const;
	std::deque<Vertex> getVertices() const;

	//Surcharges
	bool operator==(const Face& f) const;

	//Traitements
	bool areCoplanar(const Face& f) const; //teste si 2 faces sont coplanaires

	//Entrées - Sorties
	friend std::ostream& operator<<(std::ostream& os, const Face& f);

private:
	std::deque<Vertex> d_vertices; //tableau de points 3D
	int d_id;
};

#endif
