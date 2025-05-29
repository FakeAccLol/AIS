#pragma once
#include <vector>
#include <iostream>
#include <bitset>
#include <string>

using std::vector;
using std::string;

namespace functions
{
	double griewank(vector<double> x);
	double stibtaig(vector<double> x);
}

namespace gray
{
    int intToGray(int num);
	int grayToInt(int gray);
}

namespace numpy
{
	vector<double> linspace(double start, double end, int num);
	vector<double> logspace(double start, double end, int num);
}