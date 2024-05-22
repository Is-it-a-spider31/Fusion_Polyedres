#include <iostream>
#include "Algorithm.h"

#include "BruteForceAlgorithm.h"
#include "RecuitSimuleAlgorithm.h"
#include "genetic/GeneticAlgorithm.h"

#include "genetic/TurnamentSelection.h"
#include "genetic/NXCrossover.h"
#include "genetic/InsertionMutation.h"


#include <cstdlib> // Pour la fonction system()
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	// Script qui supprime les fichiers .obj eventuellement generes 
	// par d'anciennes executions du programme
	#ifdef _WIN32 // OS Windows
		system("powershell.exe -ExecutionPolicy Bypass -File scripts/delete_obj_files.ps1");
	#elif __linux__ // OS Linux
		system("./scripts/delete_obj_files.sh");
	#endif

	// Chemins des fichiers .obj avec lesquels le programme est teste
	const string MERGE_TEST_PATH = "Tests/MergeTest/";
	const string CONVEXITY_TEST_PATH = "Tests/ConvexiTest/";
	const string BUGS_TEST_PATH = "Tests/BugsTests/";

	//TEST ALGO BRUTE-FORCE
	//BruteForceAlgorithm bruteforce(MERGE_TEST_PATH+"exemple2.obj");
	//bruteforce.run();

	//TEST RECUIT SIMULE
	//RecuitSimuleAlgorithm recuit(MERGE_TEST_PATH+"exemple3.obj");
	//recuit.run();

	// TESTS CONVEXITE
	//BruteForceAlgorithm algo(CONVEXITY_TEST_PATH + "2DnotConvex.obj");
	//BruteForceAlgorithm algo(MERGE_TEST_PATH + "3plans-2Convexes.obj");
	//BruteForceAlgorithm algo(BUGS_TEST_PATH + "2DnotConvex-corrected.obj");
	//algo.test_Convexity();
	//algo.run();
  
	// TEST ECRITURE/LECTURE .OBJ
	//algo.test_WriteObj();
	//algo.test_LoadObj();

	//------------------------------------------

	// Test Crossover
	/*NXCrossover crossover(3);
	crossover.test();*/

	srand(time(NULL));
	TurnamentSelection selection;
	InsertionMutation mutation;
	NXCrossover crossover(5);

	//GeneticAlgorithm ga{MERGE_TEST_PATH+"exemple3.obj", 50, 0.5, 0.5, 200, selection, mutation};
	GeneticAlgorithm ga{MERGE_TEST_PATH+"exemple_complexe.obj", 50, 0.6, 0.4, 10000, selection, crossover, mutation};
	ga.run();


	

	//faire gaffe si la population est petite et la dimension aussi

	return 0;
}