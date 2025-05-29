#include "AISbase.h"
#include "Cellbase.h"

AISbase::AISbase(Options opt) : AIS(opt)
{

}

void AISbase::run()
{
	info.clear();
	population.clear();
	// Initial population
	for (size_t i = 0; i < params.population_size; ++i)
		population.emplace_back(std::make_unique<Cellbase>(params.dimensions, foo, params.search_area));
	
	// Run simulation
	for (size_t gen = 0; gen < params.generations; ++gen) {
		// Get best cells
		std::sort(population.begin(), population.end(), [](std::unique_ptr<Cell >& a, std::unique_ptr<Cell >& b) {
			return a->affinity < b->affinity;
			});

		/*if (population[0]->affinity < 0)
			throw __ExceptionPtrAssign;*/

		if (info.size() == 0)
			info.push_back({ gen, population[0]->affinity });

		if (info[info.size() - 1].second > population[0]->affinity)
			info.push_back({ gen, population[0]->affinity });

		if (population[0]->affinity < params.eps)
			break;

		// Save best and mutate
		std::vector<std::unique_ptr<Cell>> new_population;
		size_t elite_size = params.population_size / params.shrick_rate;

		for (size_t i = 0; i < params.population_size - elite_size; ++i) {
			new_population.push_back(dynamic_cast<Cellbase*>(population[i].get())->clone());
			new_population[i]->mutate(params.mutation_rate);
			++calls;
		}

		for (size_t i = 0; i < elite_size; ++i)
			new_population.push_back(std::move(population[i]));

		// move them
		population = std::move(new_population);

		
	}
	
}
