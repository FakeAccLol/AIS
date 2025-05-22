#pragma once
#include <random>
#include <numeric>
#include <functional>

class Antibody
{
private:
	std::mt19937 gen;

	// Функция Гриванка
	double griewank(const std::vector<double>& x);
	double stibtaig(const std::vector<double>& x);

	std::function<double(const std::vector<double>& x)> foo;

public:
	std::vector<double> position;
	double affinity;

	// Добавила значение по умолчанию для limits, нужно для корректировки cpp файла
	Antibody(size_t dim, std::pair<double, double> limits = {-20.0, 20.0});

	// Mutate and get affinity
	double operator()(double rate);

	// Just Mutation
	void mutate(double rate);

	double call_foo(const std::vector<double>& x);
};


