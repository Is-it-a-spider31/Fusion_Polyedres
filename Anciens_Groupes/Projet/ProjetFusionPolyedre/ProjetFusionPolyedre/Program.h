#ifndef PROGRAM_H
#define PROGRAM_H

#include <fstream>
#include <algorithm>
#include "Polyhedron.h"

class Program
{
public:
	Program();
	~Program();

	// Lance la proc�dure de traitement
	void run();

	// Charger le contenu d'un fichier .obj dans les structures du programme
	void loadObj(std::string nomFichier);
	void saveObj(std::string nomFichier, std::deque<Polyhedron> polyhedron_list);

	// Getters
	static std::deque<Vertex> getVertices();
	static std::deque<Face> getFaces();
	static std::deque<Polyhedron> getPolyhedrons();
	static Vertex getVertice(int i);
	static Face getFace(int i);
	static Polyhedron getPolyhedron(int i);

	//Remplissage des matrices 2D
	void fillAreMergeableMatrix(std::deque<Polyhedron> polyhedron_list);
	void fillSharedFaceMatrix(std::deque<Polyhedron>& polyhedron_list);

	// Op�rations sur les structures
	std::deque<Polyhedron> permutations(int nbelem, std::deque<Polyhedron> polyhedron_list);
	Polyhedron fusion(Polyhedron i, Polyhedron j); // Fusionne les poly�dres i et j
	std::deque<Polyhedron> merge_all(std::deque<Polyhedron> polyhedron_list);

	// Surcharge de l'op�rateur de sortie pour les structures du programme
	friend std::ostream& operator<<(std::ostream& os, const std::deque<Vertex>& v);
	friend std::ostream& operator<<(std::ostream& os, const std::deque<Face>& f);
	friend std::ostream& operator<<(std::ostream& os, const std::deque<Polyhedron>& p);

private:
	//Listes de points, faces et poly�dres
	static std::deque<Vertex> d_vertices_list;
	static std::deque<Face> d_faces_list;
	static std::deque<Polyhedron> d_polyhedron_list;

	//Matrices 2D
	std::vector<std::vector<bool>> d_areMergeableMatrix; //case ij = true si fusion possible entre poly�dres i et j
	std::vector<std::vector<std::vector<int>>> d_sharedFaceMatrix; //case ij = liste des num�ros des faces que le poly�dre i partage avec j. La case ij est diff�rente de la case ji
};

#endif