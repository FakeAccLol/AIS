#include "Simulator.h"

void Simulator::operator()(SimulatorOptions opt) {
	// Инициализация популяции
	for (size_t i = 0; i < opt.population_size; ++i)
		population.emplace_back(opt.dimensions, opt.search_area);

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

		printBest(gen, opt.dimensions);
	}
	printResult(opt.dimensions);
}

void Simulator::printBest(size_t gen, size_t dimensions) {
	std::cout << "Generation " << gen << ": Best affinity = " << population[0].affinity << '\t';
	for (size_t i = 0; i < dimensions; ++i)
		std::cout << "x" << i + 1 << " = " << population[0].position[i] << '\t';
	std::cout << std::endl;
}

void Simulator::printResult(size_t dimensions) {
	std::cout << "\nBest solution found:" << std::endl;
	for (size_t i = 0; i < dimensions; ++i)
		std::cout << "x" << i + 1 << " = " << population[0].position[i] << std::endl;
	std::cout << "Function value: " << population[0].affinity << std::endl;
}