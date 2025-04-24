#pragma once
#include <random>



class Antibody
{
private:
	std::mt19937 gen;

	// Функция Гриванка
	double griewank(const std::vector<double>& x);

public:
	std::vector<double> position;
	double affinity;

	Antibody(size_t dim);

	void mutate(double rate);
};


