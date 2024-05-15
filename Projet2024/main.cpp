#include <iostream>
#include "Algorithm.h"
#include "BrutForceAlgorithm.h"

using namespace std;

int main(int argc, char* argv[])
{
	//TO TEST MERGING ALGORITHM
	BrutForceAlgorithm algo("MergeTest/exemple3.obj");
	algo.run();

	//Algorithm algo("ConvexiTest/2DnotConvex.obj");
	// Algorithm algo("MergeTest/3plans-2Convexes.obj");
	//Algorithm algo("BugsTests/2DnotConvex-corrected.obj");
	//algo.test_Convexity();
	//algo.run();
  
	//algo.test_WriteObj();
	//algo.test_LoadObj();

	return 0;
}