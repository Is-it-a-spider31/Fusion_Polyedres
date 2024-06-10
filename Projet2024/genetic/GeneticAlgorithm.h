#pragma once
#include "../Algorithm.h"
#include <vector>
#include <iostream>

#include "Population.h"
#include "Selection.h"
#include "Crossover.h"
#include "Mutation.h"

#include <cmath>
#include "../OBJFileHandler.h"

using namespace std;

/**
 * @brief Algorithme génétique (ou GA)
*/
class GeneticAlgorithm : public Algorithm
{

public:
	/**
 * @brief Constructeur de la classe GeneticAlgorithm.
 *
 * Initialise un algorithme génétique avec les paramètres spécifiés.
 *
 * @param filename Le nom du fichier contenant les données d'entrée.
 * @param popSize La taille de la population.
 * @param probaMut La probabilité de mutation.
 * @param maxIter Le nombre maximum d'itérations.
 * @param selection L'opérateur de sélection à utiliser.
 * @param crossover L'opérateur de croisement à utiliser.
 * @param mutation L'opérateur de mutation à utiliser.
 */
	GeneticAlgorithm(const string& filename, int popSize, double probaMut, int maxIter, Selection& selection, Crossover& crossover, Mutation& mutation);
	//Ajouter un algo genetic par défaut avec selection,mutation, etc, prédefini

	/**
	 * @brief Algorithme principal du recuit simule
	*/
	void run() override;

	/**
 * @brief Affiche la population actuelle.
 */
	void printPopulation() const;

	/**
	 * @brief Sauvegarde la meilleur solution
	 * 
	 * Crée un dossier avec un id unique et stocke a l'interieur la solution au format OBJ.
	 * Point de sortie de l'algorithme.
	 */
	void exportBest();

	/**
	 * Chemin du repertoire ves lequel l'agoritme ecrit
	 * les solutions trouvees sous forme de fichiers .obj
	*/
	const string getFilePath() override;

protected:

	/**
	 * @brief Taille de la population.
	 */
	int d_popSize;

	/**
	 * @brief Nombre total de polyèdres.
	 */
	int d_dimension;

	/**
	 * @brief Nombre maximum d'itérations.
	 */
	int d_maxIteration;

	/**
	 * @brief Probabilité de mutation.
	 */
	double d_mutationProba;

	//PAS UTILISE
	//double d_crossoverProba;

	/**
 * @brief Population actuelle.
 */
	vector<vector<int>> d_pop;
	/**
 * @brief Ancienne population.
 */
	vector<vector<int>> d_oldpop;

	/**
 * @brief Scores de la population actuelle.
 */
	vector<double> d_score_pop;

	/**
 * @brief Scores de l'ancienne population.
*/
	vector<double> d_oldscore_pop;


	/**
	 * @brief Indique si la population a été redimensionner dans le cas où la taille de la population
	 * est supérieur aux nombres de solutions (permutations) possibles
	 */
	bool d_popResized = false;

	
	/**
 * @brief Pointeur vers l'objet Population utilisé par l'algorithme génétique.
 */
	Population* d_Population;

	/**
	 * @brief Pointeur vers l'opérateur de sélection utilisé par l'algorithme génétique.
	 */
	Selection* d_Selection;

	/**
	 * @brief Pointeur vers l'opérateur de croisement utilisé par l'algorithme génétique.
	 */
	Crossover* d_Crossover;

	/**
	 * @brief Pointeur vers l'opérateur de mutation utilisé par l'algorithme génétique.
	 */
	Mutation* d_Mutation;


private:	

	/**
 * @brief Affiche un graphique représentant l'évolution de l'objectif en fonction des itérations.
 *
 * Cette méthode écrit les données dans un fichier, puis génère un graphique en utilisant un objet DataWriter.
 * Le graphique affiche l'évolution de l'objectif en fonction des itérations.
 *
 * @param info Informations supplémentaires à inclure dans le graphique.
 */
	void printDataChart(const string& info);
	
	/**
 * @brief Convertit une permutation en une liste de polyèdres.
 *
 * Cette méthode prend en entrée l'index d'une permutation dans la population
 * et retourne une liste de polyèdres correspondant à cette permutation.
 *
 * @param index L'index de la permutation dans la population.
 * @return Une liste de polyèdres correspondant à la permutation.
 */
	vector<Polyedre> perm2Poly(int index);

	/**
 * @brief Liste des polyèdres correspondant à la meilleure permutation.
 */
	vector<Polyedre> d_permutScoreMax;

};

