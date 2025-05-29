#pragma once
#include <vector>

using std::vector;
using std::pair;

struct Options
{
    size_t population_size = 1000;
    size_t dimensions = 2;
    size_t generations = 1000;
    short mutation_rate = 5; // from 1 to 32000
    double shrick_rate = 100;
    double eps = 1;
    vector<pair<double, double>> search_area = { {-20, 20}, {-20, 20} };
};

