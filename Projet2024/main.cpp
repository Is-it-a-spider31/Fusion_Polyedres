#include <iostream>
#include "Algorithm.h"

using namespace std;

int main(int argc, char* argv[])
{
	Algorithm algo("ConvexiTest/cylindre.obj");

	algo.test_Convexity();

	return 0;
}