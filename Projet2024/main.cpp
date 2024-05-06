#include <iostream>
#include "Algorithm.h"

using namespace std;

int main(int argc, char* argv[])
{
	Algorithm algo("MergeTest/exemple2.obj");
	 algo.run();

	/*Algorithm algo("MergeTest/deviantMerge/NotConvexePoly.obj", "");
	algo.test_Convexity();*/


	return 0;
}