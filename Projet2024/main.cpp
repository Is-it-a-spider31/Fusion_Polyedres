#include <iostream>
#include "Algorithm.h"

using namespace std;

int main(int argc, char* argv[])
{
	Algorithm algo("ConvexiTest/cube_convex.obj");

	algo.test_Convexity();

	algo.test_WriteObj();
	algo.test_LoadObj();
	

	return 0;
}