#include <iostream>
#include "Algorithm.h"

using namespace std;

int main(int argc, char* argv[])
{
	Algorithm algo("ConvexiTest/subdiv_sphere.obj");

	algo.test_Convexity();

	return 0;
}