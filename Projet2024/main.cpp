#include <iostream>
#include "Algorithm.h"
#include "BruteForceAlgorithm.h"
#include "RecuitSimuleAlgorithm.h"

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

	//TEST ALGO BRUT-FORCE
	//BruteForceAlgorithm bruteforce("MergeTest/exemple3.obj");
	//bruteforce.run();

	//TEST RECUIT SIMULE
	RecuitSimuleAlgorithm recuit("MergeTest/exemple3.obj");
	recuit.run();


	// TESTS CONVEXITE
	//Algorithm algo("ConvexiTest/2DnotConvex.obj");
	//Algorithm algo("MergeTest/3plans-2Convexes.obj");
	//Algorithm algo("BugsTests/2DnotConvex-corrected.obj");
	//algo.test_Convexity();
	//algo.run();
  
	// TEST ECRITURE/LECTURE .OBJ
	//algo.test_WriteObj();
	//algo.test_LoadObj();

	return 0;
}