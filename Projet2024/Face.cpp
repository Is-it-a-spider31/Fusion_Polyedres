#include "Face.h"


/**
 * @brief Contructeur a partir des sommets
 *
 * @param sommets sommets de la face
 * @param id identifiant unique de la face
*/
Face::Face(const vector<Point> lesPoints, int id) {

	points = lesPoints;
	d_id = id;
}

// GETTERS

/**
 * @brief renvoie le sommet i
 * @param i indice du sommet
 * @return le point correspondant au sommet voulu
*/
Point Face::getSommet(int i) { return d_sommets[i]; }

/**
 * @brief renvoie l'identifiant de la face
 * @return l'id de la face
*/
int Face::getId() const
{
	return d_id;
}


// OPERATEUR REDEFINI

bool Face::operator==(Face f)
{
	if (d_sommets.size() == f.d_sommets.size()) {
		int pointsEnCommun = 0;

		for (int i = 0; i < d_sommets.size(); ++i) {
			for (int j = 0; j < points.size(); ++j)
			{
				if (points[i] == f.d_sommets[j])
				{

					pointsEnCommun++;
				}
			}
		}

		return pointsEnCommun == d_sommets.size();
	}
	return false;
}
