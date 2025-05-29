#include "AISmod.h"
#include "Cellmod.h"

AISmod::AISmod(Options opt) : AIS(opt)
{
}

void AISmod::run()
{
	// Initial population
	for (size_t i = 0; i < params.population_size; ++i)
		population.emplace_back(std::make_unique<Cellmod>(params.dimensions, foo, params.search_area));

	// Run simulation
	for (size_t gen = 0; gen < params.generations; ++gen) {
		// Get best cells
		std::sort(population.begin(), population.end(), [](std::unique_ptr<Cell >& a, std::unique_ptr<Cell >& b) {
			return a->affinity < b->affinity;
			});

		// Save best
		std::vector<std::unique_ptr<Cell>> new_population;
		size_t elite_size = params.population_size / params.shrick_rate;
		for (size_t i = 0; i < elite_size; ++i)
			new_population.push_back(std::move(population[i]));

		// Mutate others
		for (size_t i = elite_size; i < params.population_size; ++i) {
			population[i]->mutate(params.mutation_rate);
			new_population.push_back(std::move(population[i]));
			++calls;
		}

		// move them
		population = std::move(new_population);

		info.push_back({ gen, population[0]->affinity });
	}
}
