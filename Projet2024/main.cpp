#include <iostream>
#include "Algorithm.h"
#include "BrutForceAlgorithm.h"
#include "GeneticAlgorithm.h"

#include <cstdlib> // Pour la fonction system()

using namespace std;

int main(int argc, char* argv[])
{
	// Script qui supprime les fichiers .obj du repertoire "MergeTest/generated"
	#ifdef _WIN32 // OS Windows
		system("powershell.exe -ExecutionPolicy Bypass -File delete_obj_files.ps1");
	#elif __linux__ // OS Linux
		system("./delete_obj_files.sh");
	#endif

	//TO TEST BRUT FORCE ALGORITHM
	//BrutForceAlgorithm algo("MergeTest/exemple3.obj");

	//algo.run();

	//Algorithm algo("ConvexiTest/2DnotConvex.obj");
	//Algorithm algo("MergeTest/3plans-2Convexes.obj");
	//Algorithm algo("BugsTests/2DnotConvex-corrected.obj");
	//algo.test_Convexity();
	//algo.run();
  
	//algo.test_WriteObj();
	//algo.test_LoadObj();

	//------------------------------------------
	GeneticAlgorithm ga{"MergeTest/exemple3.obj", 500000, 0.5, 0.5, 100000};
	ga.run();

	//faire gaffe si la population est petite et la dimension aussi

	return 0;
}