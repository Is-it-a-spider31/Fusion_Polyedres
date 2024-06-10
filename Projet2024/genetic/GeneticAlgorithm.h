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
 * @brief Algorithme g�n�tique (ou GA)
*/
class GeneticAlgorithm : public Algorithm
{

public:
	/**
 * @brief Constructeur de la classe GeneticAlgorithm.
 *
 * Initialise un algorithme g�n�tique avec les param�tres sp�cifi�s.
 *
 * @param filename Le nom du fichier contenant les donn�es d'entr�e.
 * @param popSize La taille de la population.
 * @param probaMut La probabilit� de mutation.
 * @param maxIter Le nombre maximum d'it�rations.
 * @param selection L'op�rateur de s�lection � utiliser.
 * @param crossover L'op�rateur de croisement � utiliser.
 * @param mutation L'op�rateur de mutation � utiliser.
 */
	GeneticAlgorithm(const string& filename, int popSize, double probaMut, int maxIter, Selection& selection, Crossover& crossover, Mutation& mutation);
	//Ajouter un algo genetic par d�faut avec selection,mutation, etc, pr�defini

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
	 * Cr�e un dossier avec un id unique et stocke a l'interieur la solution au format OBJ.
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
	 * @brief Nombre total de poly�dres.
	 */
	int d_dimension;

	/**
	 * @brief Nombre maximum d'it�rations.
	 */
	int d_maxIteration;

	/**
	 * @brief Probabilit� de mutation.
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
	 * @brief Indique si la population a �t� redimensionner dans le cas o� la taille de la population
	 * est sup�rieur aux nombres de solutions (permutations) possibles
	 */
	bool d_popResized = false;

	
	/**
 * @brief Pointeur vers l'objet Population utilis� par l'algorithme g�n�tique.
 */
	Population* d_Population;

	/**
	 * @brief Pointeur vers l'op�rateur de s�lection utilis� par l'algorithme g�n�tique.
	 */
	Selection* d_Selection;

	/**
	 * @brief Pointeur vers l'op�rateur de croisement utilis� par l'algorithme g�n�tique.
	 */
	Crossover* d_Crossover;

	/**
	 * @brief Pointeur vers l'op�rateur de mutation utilis� par l'algorithme g�n�tique.
	 */
	Mutation* d_Mutation;


private:	

	/**
 * @brief Affiche un graphique repr�sentant l'�volution de l'objectif en fonction des it�rations.
 *
 * Cette m�thode �crit les donn�es dans un fichier, puis g�n�re un graphique en utilisant un objet DataWriter.
 * Le graphique affiche l'�volution de l'objectif en fonction des it�rations.
 *
 * @param info Informations suppl�mentaires � inclure dans le graphique.
 */
	void printDataChart(const string& info);
	
	/**
 * @brief Convertit une permutation en une liste de poly�dres.
 *
 * Cette m�thode prend en entr�e l'index d'une permutation dans la population
 * et retourne une liste de poly�dres correspondant � cette permutation.
 *
 * @param index L'index de la permutation dans la population.
 * @return Une liste de poly�dres correspondant � la permutation.
 */
	vector<Polyedre> perm2Poly(int index);

	/**
 * @brief Liste des poly�dres correspondant � la meilleure permutation.
 */
	vector<Polyedre> d_permutScoreMax;

};

