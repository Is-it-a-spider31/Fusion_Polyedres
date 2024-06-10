#pragma once

#include "Face.h"
#include <set>


/**
 * @brief Represente un polyedre
*/
class Polyedre
{

public:

	/**
	* Constructeur par defaut
	*/
	Polyedre();

	/**
	 * @brief Constructeur
	 * 
	 * @param id Identifiant unique
	*/
	Polyedre(int id);
	
	/**
	 * @brief Constructeur par copie en excluant des faces
	 * 
	 * @param copy Polyedre a copier
	 * @param sharedFaces Faces a ne pas copier
	*/
	Polyedre(const Polyedre& copy, const vector<Face>& excludedFaces);

	/**
	 * @brief Liste des faces du polyedre
	*/
	vector<Face> faces;

	/**
	 * @brief Fusionne 2 polyedres si possible
	 *
	 * Si la fusion n'est pas possible, retourne un polyedre
	 *	vide avec son id = -1
	 *
	 * @param poly1
	 * @param poly2
	 * @return Le polyedre fusionne (id = -1 si pas possible)
	*/
	static Polyedre merge2Polyhedra(const Polyedre& poly1, const Polyedre& poly2);

	/**
	 * @return true si le polyedre est convexe, faux sinon
	*/
	bool isConvex() const;

	/**
	 * @brief Calcul si le polyedre est convexe ou pas.
	 *
	 * Pour savoir si un polyedre est convexe, le principe est de verifier
	 * si pour chaque face, tous les sommets sont du meme cote.
	 * Cette methode met a jour un attribut qui est accessible
	 * avec la fonction @ref isConvexe (pour eviter de refaire le calcul)
	*/
	void computeConvexity();

	/**
	 * @brief Met a jour l'id et les composants du polyedre.
	 * 
	 * Met a jour l'ensemble des composants a partir de ceux des 2
	 * polyedres en parametres.
	 * Puis met a jour l'identifiant a partir de cet ensemble
	 * 
	 * @param poly1
	 * @param poly2 
	*/
	void updateIdAndCompnenents(
		const Polyedre& poly1,
		const Polyedre& poly2
	);

	
	/**
 * @brief Renvoie l'identifiant du polyèdre.
 * @return L'identifiant du polyèdre.
 */
	string getId() const;

	/**
	 * @brief Renvoie le nom du matériau (MTL) du polyèdre.
	 * @return Le nom du matériau du polyèdre.
	 */
	string getMTL() const;

	/**
	 * @brief Renvoie la liste des faces du polyèdre.
	 * @return Un vecteur contenant les faces du polyèdre.
	 */
	vector<Face> getFaces() const;


	/**
	 * @return Le nombre de sous-polyèdres qui composent le polyedre actuel
	*/
	int getNbComponents() const;

	
	/**
	 * @brief Définit le nom du matériau (MTL) du polyèdre.
	 * @param name Le nom du matériau à attribuer au polyèdre.
	 */
	void setMTL(string name);

	/**
	 * @brief Définit l'identifiant du polyèdre.
	 * @param id L'identifiant à attribuer au polyèdre.
	 */
	void setId(const int id);

	
	/**
 * @brief Compare les identifiants de deux polyèdres.
 *
 * @param otherPoly Le polyèdre à comparer.
 * @return true si l'identifiant de ce polyèdre est inférieur à celui de otherPoly, sinon false.
 */
	bool operator<(const Polyedre& otherPoly) const;

	/**
	 * @brief Vérifie si deux polyèdres sont égaux en comparant leurs faces.
	 *
	 * @param poly Le polyèdre à comparer.
	 * @return true si les polyèdres ont le même nombre de faces et que toutes leurs faces sont communes, sinon false.
	 */
	bool operator==(const Polyedre& poly) const;

	/**
	 * @brief Affiche le polyèdre dans un flux de sortie.
	 *
	 * @param os Le flux de sortie où le polyèdre sera affiché.
	 * @param p Le polyèdre à afficher.
	 * @return Une référence au flux de sortie après l'affichage du polyèdre.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Polyedre& p);


private:
	/**
	 * @brief Identifiant unique du polyedre
	*/
	string d_id;

	/**
	 * @brief Etat convexe / non convexe du polyèdre
	*/
	bool d_isConvex;

	/**
	 * @brief Sous polyedres qui constituent le polyedre actuel.
	 * Ordonne, pas de doublons
	*/
	set<int> d_components;

	/**
	 * @brief Pas utilisee
	*/
	string d_texture;

	/**
	 * @brief Renvoie les faces communes entre 2 polyedres
	 *
	 * @param poly1
	 * @param poly2
	 * @return la liste des faces communes entre les 2 polyedres
	*/
	static vector<Face> getSharedFaces(const Polyedre& poly1, const Polyedre& poly2);

	/*
	 * @brief Fusionne 2 polyedres adjacents (au moins une face commune).
	 *
	 * Au moins un des deux polyedres doit avoir plus d'une face.
	 *
	 * @param poly1 1er polyedre
	 * @param poly2 2eme polyedre
	 * @param sharedFaces Liste des faces communes aux 2 polyedres
	 *
	 * @return Le polyedre resultant de la fusion
	*/
	static Polyedre merge2AdjacentPolyhedra(const Polyedre& poly1, const Polyedre& poly2, const vector<Face> sharedFaces);

	/**
	 * @brief Fusionne 2 polygones
	 *
	 * Un polygone est un polyedre avec un volume nul
	 * (c'est-a-dire un polyedre avec une seule face)
	 *
	 * @param poly1
	 * @param poly2
	 * @return Le polygone resultant de la fusion (si id=-1, alors fusion pas possible)
	*/
	static Polyedre merge2Polygones(const Polyedre& poly1, const Polyedre& poly2);

};

