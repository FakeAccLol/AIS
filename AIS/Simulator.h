#pragma once
#include "Antibody.h"
#include <iostream>

class Simulator
{
public:
	class SimulatorOptions
	{
	public:
		size_t population_size;
		size_t dimensions;
		size_t generations;
		double mutation_rate;
		double shrick_rate;
		SimulatorOptions(size_t population_size = 1000, size_t dimensions = 2, size_t generations = 1000, double mutation_rate = 5, double shrick_rate = 100)
			: population_size(population_size), dimensions(dimensions), generations(generations), mutation_rate(mutation_rate), shrick_rate(shrick_rate) {};
	};

	// Алгоритм клональной селекции
	void operator()(SimulatorOptions opt) {
		std::vector<Antibody> population;

		// Инициализация популяции
		for (size_t i = 0; i < opt.population_size; ++i) {
			population.emplace_back(opt.dimensions);
		}

		// Основной цикл
		for (size_t gen = 0; gen < opt.generations; ++gen) {
			// Сортировка по аффинности
			std::sort(population.begin(), population.end(), [](const Antibody& a, const Antibody& b) {
				return a.affinity < b.affinity;
				});

			// Клонирование лучших антител
			std::vector<Antibody> new_population;
			size_t elite_size = opt.population_size / opt.shrick_rate;
			for (size_t i = 0; i < elite_size; ++i)
				new_population.push_back(population[i]);

			// Мутация клонов
			for (size_t i = elite_size; i < opt.population_size; ++i) {
				population[i].mutate(opt.mutation_rate);
				new_population.push_back(population[i]);
			}

			// Обновление популяции
			population = std::move(new_population);

			// Вывод лучшего решения
			std::cout << "Generation " << gen << ": Best affinity = " << population[0].affinity << '\t';
			for (size_t i = 0; i < opt.dimensions; ++i)
				std::cout << "x" << i + 1 << " = " << population[0].position[i] << '\t';
			std::cout << std::endl;
		}

		// Вывод окончательного результата
		std::cout << "\nBest solution found:" << std::endl;
		for (size_t i = 0; i < opt.dimensions; ++i)
			std::cout << "x" << i + 1 << " = " << population[0].position[i] << std::endl;
		std::cout << "Function value: " << population[0].affinity << std::endl;
	}
};

