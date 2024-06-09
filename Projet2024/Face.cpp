#include "Face.h"


/**
 * @brief Contructeur a partir des sommets
 *
 * @param sommets sommets de la face
 * @param id identifiant unique de la face
*/
Face::Face(const vector<Point> lesPoints, int id) {

	d_sommets = lesPoints;
	d_id = id;
}


/**
* @brief Teste si la face (polygone) est convexe
* @return true si convexe, false sinon
*/
bool Face::isConvex() const
{
	size_t size = d_sommets.size();
	bool isPositive = false;
	bool isNegative = false;

	for (int i = 0; i < size; ++i) {

		Point u = d_sommets[i] - d_sommets[(i + 1) % size];
		Point v = d_sommets[(i + 2) % size] - d_sommets[(i + 1) % size];

		// Produit vectoriel entre u et v
		// Poduit scalaire avec le vecteur (0, 1, 0) pour d�terminer l'orientation
		double cp = u.crossProduct(v)
			.dotProduct(Point(0,0,1,0));

		if (cp > 0) {
			isPositive = true;
		}
		else if (cp < 0) {
			isNegative = true;
		}

		// Si les produits vectoriels ont des orientations opposees, 
		// le polygone n'est pas convexe
		if (isPositive && isNegative) {
			return false;
		}
	}

	// Si tous les produits vectoriels ont la m�me orientation,
	// le polygone est convexe
	return true;
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


/**
 * @brief Compare deux objets Face pour l'�galit�.
 *
 * Cette m�thode v�rifie si deux objets Face sont �gaux en comparant leurs sommets.
 * Deux objets Face sont consid�r�s comme �gaux si et seulement si ils ont le m�me nombre de sommets
 * et que chaque sommet de l'un est pr�sent dans l'autre.
 *
 * @param f L'objet Face � comparer.
 * @return true si les deux objets Face sont �gaux, false sinon.
 */
bool Face::operator==(const Face f) const
{
	if (d_sommets.size() == f.d_sommets.size()) {
		int pointsEnCommun = 0;

		for (int i = 0; i < d_sommets.size(); ++i) {
			for (int j = 0; j < d_sommets.size(); ++j)
			{
				if (d_sommets[i] == f.d_sommets[j])
				{
					pointsEnCommun++;
				}
			}
		}

		// Nombres de sommets en commun = nombre de sommets de chaques faces
		return ((pointsEnCommun == d_sommets.size()) && (pointsEnCommun == f.d_sommets.size()));
	}
	return false;
}

/**
* @brief Op�rateur de flux de sortie pour les objets Face.
*
* Cette fonction amie permet d'�crire un objet Face dans un flux de sortie.
* Elle formate les donn�es de l'objet Face pour une sortie lisible.
*
* @param os Le flux de sortie dans lequel l'objet Face est �crit.
* @param f L'objet Face � �crire dans le flux de sortie.
* @return Une r�f�rence au flux de sortie apr�s l'�criture de l'objet Face.
*/
std::ostream& operator<<(std::ostream& os, const Face& f)
{
	os << "f ";
	for (const auto& point : f.d_sommets)
	{
		os << point.getId() << " ";
	}
	os << std::endl;
	return os;
}
