#pragma once
#include "Antibody.h"
#include <iostream>
#include <vector>  
#include <algorithm>   // Для std::sort (если используется в заголовке)

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
        std::pair<double, double> search_area;
        SimulatorOptions(size_t population_size = 1000, size_t dimensions = 2, size_t generations = 1000,
            double mutation_rate = 5, double shrick_rate = 100, std::pair<double, double> search_area = { -20, 20 })
            : population_size(population_size), dimensions(dimensions), generations(generations),
            mutation_rate(mutation_rate), shrick_rate(shrick_rate), search_area(search_area) {
        };
    };

    void operator()(SimulatorOptions opt);
    
    // Добавила новый метод, чтобы это все тестить :))))
    const std::vector<Antibody>& getPopulation() const { return population; }

private:
    std::vector<Antibody> population;

    void printBest(size_t gen, size_t dimensions);
    void printResult(size_t dimensions);
};

