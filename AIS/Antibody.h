#pragma once
#include <random>
#include <numeric>


class Antibody
{
private:
	std::mt19937 gen;

	// Функция Гриванка
	double griewank(const std::vector<double>& x);

public:
	std::vector<double> position;
	double affinity;

	// Create
	Antibody(size_t dim, std::pair<double, double> limits);

	// Mutate and get affinity
	double operator()(double rate);

	// Just Mutation
	void mutate(double rate);
};


