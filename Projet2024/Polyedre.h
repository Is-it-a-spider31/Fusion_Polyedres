#pragma once

#include "Face.h"

/**
 * @brief Represente un polyedre
*/
class Polyedre
{

public:

	/**
	 * @brief Constructeur par defaut
	 * 
	 * @param id Identifiant unique
	*/
	Polyedre(int id);

	/**
	 * @brief Liste des faces du polyedre
	*/
	vector<Face> faces;

	// GETTER
	int getId() const;

	// OPERATEURS 

private:
	/**
	 * @brief Identifiant unique du polyedre
	*/
	int d_id;
};

