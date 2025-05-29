#pragma once
#include <vector>

using std::vector;
using std::pair;

class Options
{
public:
    size_t population_size;
    size_t dimensions;
    size_t generations;
    short mutation_rate; // from 1 to 32000
    double shrick_rate;
    vector<pair<double, double>> search_area;
    Options(size_t population_size = 1000, size_t dimensions = 2, size_t generations = 1000,
        ushort mutation_rate = 5, double shrick_rate = 100, vector<pair<double, double>> search_area = {})
        : population_size(population_size), dimensions(dimensions), generations(generations),
        mutation_rate(mutation_rate), shrick_rate(shrick_rate), search_area(search_area) {
    };
};

