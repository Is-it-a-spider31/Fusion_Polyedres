#include <iostream>
#include "Algorithm.h"

using namespace std;

int main(int argc, char* argv[])
{
	//TO TEST MERGING ALGORITHM
	//Algorithm algo("MergeTest/exemple3.obj");
	Algorithm algo("ConvexiTest/cube_convex.obj");
	algo.run();


	/*Algorithm algo("ConvexiTest/normal_sphere.obj");
	algo.test_Convexity();
 */
  
	algo.test_WriteObj();
	//algo.test_LoadObj();

	return 0;
}