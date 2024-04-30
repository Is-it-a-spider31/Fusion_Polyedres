#include "Program.h"

std::deque<Vertex> Program::d_vertices_list = std::deque<Vertex>();
std::deque<Face> Program::d_faces_list = std::deque<Face>();
std::deque<Polyhedron> Program::d_polyhedron_list = std::deque<Polyhedron>();

Program::Program()
{
}

Program::~Program()
{
}

void Program::run() {
	std::string nomFichier = "exemple3.obj";
	loadObj(nomFichier);

	fillSharedFaceMatrix(d_polyhedron_list);
	fillAreMergeableMatrix(d_polyhedron_list);

	saveObj("exemple3result.obj", permutations(d_polyhedron_list.size(), d_polyhedron_list));
	std::cout << "Fin" << std::endl;
}

void Program::loadObj(std::string nomFichier) {
	double x, y, z;
	std::string str;
	std::string object_name;
	std::ifstream file;

	file.open(nomFichier);

	for (int i = 1; !(file >> str).fail() && str == "v"; ++i) {
		file >> x >> y >> z;
		Vertex temp_vertex(i, x, y, z);
		d_vertices_list.push_back(temp_vertex);
	}

	int j = 0;
	for (int i = 0; str == "g"; ++i) {
		file >> object_name;
		d_polyhedron_list.push_back(Polyhedron(i));

		// On récupère l'id des vertices pour chaque face et on ajoute ces dernières à un nouveau polyèdre, qu'on ajoute à la liste
		file >> str;
		while (str == "f") {
			std::deque<Vertex> temp_vertices;

			// Tant que le fichier retourne un id de vertex on l'ajoute à notre vecteur de vertex temporaire
			while (!(file >> str).fail() && str != "f" && str != "g") {
				temp_vertices.push_back(d_vertices_list[std::stoi(str) - 1]);
			}

			Face temp_face(temp_vertices, j);
			d_faces_list.push_back(temp_face);
			d_polyhedron_list[i].addFace(j);
			++j;
			temp_vertices.clear();
		}
	}
	file.close();
}

void Program::saveObj(std::string nomFichier, std::deque<Polyhedron> polyhedron_list) {
	std::ofstream file;

	file.open(nomFichier);

	for (unsigned int i = 0; i < d_vertices_list.size(); ++i) {
		file << d_vertices_list[i];
	}
	file << std::endl;

	for (unsigned int i = 0; i < polyhedron_list.size(); ++i) {
		file << polyhedron_list[i];
	}
	file.close();
}


// Getters

std::deque<Vertex> Program::getVertices() { return d_vertices_list; }

std::deque<Face> Program::getFaces() { return d_faces_list; }

std::deque<Polyhedron> Program::getPolyhedrons() { return d_polyhedron_list; }

Vertex Program::getVertice(int i) { return d_vertices_list[i]; }

Face Program::getFace(int i) { return d_faces_list[i]; }

Polyhedron Program::getPolyhedron(int i) { return d_polyhedron_list[i]; }


// Remplissage des matrices 2D

void Program::fillAreMergeableMatrix(std::deque<Polyhedron> polyhedron_list) {
	d_areMergeableMatrix.resize(polyhedron_list.size());
	for (int i = 0; i < d_areMergeableMatrix.size(); ++i) {
		d_areMergeableMatrix[i].resize(polyhedron_list.size());
	}

	for (int i = 0; i < polyhedron_list.size(); i++) {
		for (int j = i + 1; j < polyhedron_list.size(); j++) {
			// Si le tableau est vide, les deux polyèdres n'ont pas de face en commun
			if (!d_sharedFaceMatrix[i][j].empty()) {
				if (fusion(polyhedron_list[i], polyhedron_list[j]).isConvex()) {
					d_areMergeableMatrix[i][j] = true;
					d_areMergeableMatrix[j][i] = true;
				}
				else {
					d_areMergeableMatrix[i][j] = false;
					d_areMergeableMatrix[j][i] = false;
				}
			}
			else {
				d_areMergeableMatrix[i][j] = false;
				d_areMergeableMatrix[j][i] = false;
			}
		}
	}
}

void Program::fillSharedFaceMatrix(std::deque<Polyhedron>& polyhedron_list) {
	d_sharedFaceMatrix.resize(polyhedron_list.size());
	for (int i = 0; i < d_sharedFaceMatrix.size(); ++i) {
		d_sharedFaceMatrix[i].resize(polyhedron_list.size());
	}

	// Mise à jour de l'id des polyèdres afin que leur numéro se suivent, correspondent à la taille de la matrice et permettent les comparaisons via ce tableau
	for (int i = 0; i < polyhedron_list.size(); ++i) {
		polyhedron_list[i].setId(i);
	}

	for (int i = 0; i < polyhedron_list.size(); i++) {
		for (int j = i + 1; j < polyhedron_list.size(); j++) {
			if (i != j) {
				d_sharedFaceMatrix[i][j] = polyhedron_list[i].getSharedFaces(d_polyhedron_list[j]);
				d_sharedFaceMatrix[j][i] = polyhedron_list[j].getSharedFaces(d_polyhedron_list[i]);
			}
		}
	}
}


// Opérations sur les structures

std::deque<Polyhedron> Program::permutations(int nbelem, std::deque<Polyhedron> polyhedron_list) {
	if (nbelem == 1) {
		std::deque<Polyhedron> merge_result, previous_merge_result;

		// On lance une première fois la fonction d'assemblage des polyèdres sur le tableau de base
		merge_result = merge_all(polyhedron_list);
		
		do {
			previous_merge_result = merge_result; // On stocke le résultat précedent avant de relancer l'assemblage sur le résultat.
			merge_result = merge_all(merge_result);
		} while (merge_result.size() != previous_merge_result.size()); // Quand plus aucune fusion n'est effectuée on passe à l'essai suivant
		
		return merge_result;
	}
	else {
		std::deque<Polyhedron> temp_deque, best_result = polyhedron_list;
		for (int i = 0; i < nbelem; ++i) {
			temp_deque = permutations(nbelem - 1, polyhedron_list);
			std::swap(polyhedron_list[i], polyhedron_list[nbelem - 1]);

			if (temp_deque.size() < best_result.size()) {
				best_result = temp_deque;
			}
		}
		
		return best_result;
	}
}

Polyhedron Program::fusion(Polyhedron p1, Polyhedron p2) {
	int p1id = p1.getId(), p2id = p2.getId();
	Polyhedron p(p1id);

	// On commence la suppression par la fin : supprimer les premiers éléments avant décalerait les éléments restants susceptibles d'être supprimés. Il s'agit de supprimer les faces communes
	for (int i = d_sharedFaceMatrix[p1id][p2id].size() - 1; i >= 0; --i) {
		p1.deleteFace(d_sharedFaceMatrix[p1id][p2id][i]);
	}
	for (int i = d_sharedFaceMatrix[p2id][p1id].size() - 1; i >= 0; --i) {
		p2.deleteFace(d_sharedFaceMatrix[p2id][p1id][i]);
	}

	// On fait une concaténations des faces de p1 et p2 dans p 
	for (int i = 0; i < p1.getFaces().size(); ++i) {
		p.addFace(p1.getFaceId(i));
	}
	for (int i = 0; i < p2.getFaces().size(); ++i) {
		p.addFace(p2.getFaceId(i));
	}
	
	return p;
}

std::deque<Polyhedron> Program::merge_all(std::deque<Polyhedron> polyhedron_list) {
	int j = 0;
	// Lorsqu'un polyèdre a été fusionné, il ne faut plus l'utiliser pour une autre fusion pour le reste de l'exécution de cette fonction. Le tableau suivant permet cette vérification
	std::vector<bool> is_available(polyhedron_list.size(), true);
	std::deque<Polyhedron> fusion_list = std::deque<Polyhedron>();

	// On met à jour la matrice des faces partagées qui est utilisée pour la fonction fusion, ce qui est nécessaire pour le moment mais doit disparaître à terme
	fillSharedFaceMatrix(polyhedron_list);

	// On fusionne chaque polyèdre de la liste avec le premier polyèdre qui convient s'il n'a pas déjà été utilisé dans une autre fusion
	for (int i = 0; i < polyhedron_list.size(); ++i) {
		for (j = i + 1; j < polyhedron_list.size(); ++j) {
			if (!d_sharedFaceMatrix[i][j].empty()) {
				if (fusion(polyhedron_list[i], polyhedron_list[j]).isConvex() && (is_available[i] && is_available[j])) {
					is_available[i] = false;
					is_available[j] = false;
					fusion_list.push_back(fusion(polyhedron_list[i], polyhedron_list[j]));
				}
			}
		}
		// Si le polyèdre i n'a pas été utilisé pour une fusion, on le rejoute dans la liste de polyèdres renvoyée par cette fonction
		if (is_available[i]) {
			fusion_list.push_back(polyhedron_list[i]);
		}
	}
	
	return fusion_list;
}


// Surcharges ostream

std::ostream& operator<<(std::ostream& os, const std::deque<Vertex>& v) {
	for (unsigned int i = 0; i < v.size(); i++) {
		os << v[i];
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const std::deque<Face>& f) {
	for (unsigned int i = 0; i < f.size(); i++) {
		os << f[i] << " ";
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, const std::deque<Polyhedron>& p) {
	for (unsigned int i = 0; i < p.size(); i++) {
		os << p[i] << " ";
	}
	os << std::endl;

	return os;
}
