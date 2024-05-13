#include <iostream>
#include "Algorithm.h"

using namespace std;

int main(int argc, char* argv[])
{
	//TO TEST MERGING ALGORITHM
	//Algorithm algo("MergeTest/exemple3.obj");
	//algo.run();


	Algorithm algo("ConvexiTest/2FacesPlates1SegmentCommun.obj");
	algo.test_Convexity();
	algo.run();
  
	//algo.test_WriteObj();
	//algo.test_LoadObj();

	return 0;
}