#include <iostream>
#include "Algorithm.h"

using namespace std;

int main(int argc, char* argv[])
{
	Algorithm algo("ConvexiTest/normal_sphere.obj");

	algo.test_Convexity();
	algo.test_WriteObj();

	return 0;
}