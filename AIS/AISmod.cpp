#include "AISmod.h"
#include "Cellmod.h"
#include "myutils.h"

AISmod::AISmod(Options opt) : AIS(opt)
{
}


void AISmod::run()
{
	population.clear();
	// Initial population
	for (size_t i = 0; i < params.population_size; ++i)
		population.emplace_back(std::make_unique<Cellmod>(params.dimensions, foo, params.search_area));

	// Run simulation
	for (size_t gen = 0; gen < params.generations; ++gen) {
		// Get best cells
		std::sort(population.begin(), population.end(), [](std::unique_ptr<Cell >& a, std::unique_ptr<Cell >& b) {
			return a->affinity < b->affinity;
			});

		if (info.size() == 0)
			info.push_back({ gen, population[0]->affinity });

		if (info[info.size() - 1].second > population[0]->affinity)
			info.push_back({ gen, population[0]->affinity });

		if (population[0]->affinity < params.eps)
			break;

		// Save best and mutate
		std::vector<std::unique_ptr<Cell>> new_population;
		size_t elite_size = params.population_size / params.shrick_rate;
		for (size_t i = 0; i < elite_size; ++i)
			new_population.push_back(dynamic_cast<Cellmod*>(population[i].get())->clone());
		vector<double> distr = numpy::logspace(0, params.population_size - elite_size, elite_size);
		vector<int> idistr;
		std::transform(distr.begin(), distr.end(), idistr.begin(),
			[](double d) { return static_cast<int>(d); });
		for (int i = 0; i < idistr.size(); ++i)
			for (int j = 0; j < idistr[i]; ++j) {
				std::unique_ptr<Cellmod> cell = dynamic_cast<Cellmod*>(population[i].get())->clone();
				cell->mutate(params.mutation_rate);
				new_population.push_back(std::move(cell));
				++calls;
			}


		for (size_t i = new_population.size() - 1; i < params.population_size; ++i) {
			new_population.push_back(dynamic_cast<Cellmod*>(population[0].get())->clone());
			new_population[i]->mutate(params.mutation_rate);
			++calls;
		}

		

		// move them
		population = std::move(new_population);
	}
}
