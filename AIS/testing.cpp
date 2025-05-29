#include "testing.h"

/*
	Нужные метрики:
	Время
	Сходимость
	Кол-во вызовов
*/

void testing::testPopulationSize()
{
	vector<size_t> numbers = { 100, 1000, 10000, 100000, 1000000 };
	for (size_t& pop_size : numbers) {
		Options opt(pop_size, 2, 1000, 100, 100, { {-20, 20}, {-20, 20} });

	}
}

void testing::testDimSize()
{
	vector<size_t> numbers = { 2, 5, 10, 15, 20 };
	for (size_t& dim_size : numbers) {
		Options opt(5000, dim_size, 1000, 100, 100, { {-20, 20}, {-20, 20} });

	}
}

void testing::testGenAmount()
{
	vector<size_t> numbers = { 100, 1000, 10000, 100000, 1000000 };
	for (size_t& gens : numbers) {
		Options opt(5000, 2, gens, 100, 100, { {-20, 20}, {-20, 20} });

	}
}

void testing::testMutationRate()
{
	vector<size_t> numbers = { 100, 1000, 5000, 15000, 30000, 60000 };
	for (size_t& mut_rate : numbers) {
		Options opt(5000, 2, 1000, mut_rate, 100, { {-20, 20}, {-20, 20} });

	}
}

void testing::testShrinkRate()
{
	vector<double> numbers = { 10, 50, 100, 500, 1000 };
	for (double& shrink_rate : numbers) {
		Options opt(5000, 2, 1000, 100, shrink_rate, { {-20, 20}, {-20, 20} });

	}
	
}
