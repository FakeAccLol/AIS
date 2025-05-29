#pragma once
#include <vector>
#include <functional>
#include <random>


using std::vector;
using std::pair;
using std::function;

class Cell
{
public:
	std::mt19937 gen;
	vector<double> position;
	double affinity;

	Cell(size_t dim, function<double(vector<double> x)> f, vector<pair<double, double>> bounds = { { -20.0, 20.0 }, { -20.0, 20.0 } });

	// Mutate and get affinity
	double operator()(int rate);

	// Just Mutation
	virtual void mutate(int rate) = 0;

protected:
	function<double(vector<double> x)> foo;
	vector<pair<double, double>> bounds;
};

