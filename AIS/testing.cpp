#include "testing.h"
#include <chrono>
#include <vector>
#include <memory>
#include <iostream>

/*
    Нужные метрики:
    Время
    Сходимость
    Кол-во вызовов
*/

using namespace std::chrono;

vector<double> testing::testPopulationSize(std::unique_ptr<AIS> method)
{
    vector<size_t> numbers = { 100, 1000, 10000, 100000, 1000000 };
    vector<double> timings;

    for (size_t& pop_size : numbers) {
        Options opt(pop_size, 2, 1000, 100, 100, { {-20, 20}, {-20, 20} });
        (*method)(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        method->calls; // нужно ещё это
        method->info; // и это

        timings.push_back(duration<double>(end - start).count());
    }

    return timings;
}

vector<double> testing::testDimSize(std::unique_ptr<AIS> method)
{
    vector<size_t> numbers = { 2, 5, 10, 15, 20 };
    vector<double> timings;

    for (size_t& dim_size : numbers) {
        vector<pair<double, double>> bounds;
        for (size_t i = 0; i < dim_size; ++i)
            bounds.push_back({ -20, 20 });
        Options opt(5000, dim_size, 1000, 100, 100, bounds);
        (*method)(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        timings.push_back(duration<double>(end - start).count());
    }

    return timings;
}

vector<double> testing::testGenAmount(std::unique_ptr<AIS> method)
{
    vector<size_t> numbers = { 100, 1000, 10000, 100000, 1000000 };
    vector<double> timings;

    for (size_t& gens : numbers) {
        Options opt(5000, 2, gens, 100, 100, { {-20, 20}, {-20, 20} });
        (*method)(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        timings.push_back(duration<double>(end - start).count());
    }

    return timings;
}

vector<double> testing::testMutationRate(std::unique_ptr<AIS> method)
{
    vector<size_t> numbers = { 100, 1000, 5000, 15000, 30000, 60000 };
    vector<double> timings;

    for (size_t& mut_rate : numbers) {
        Options opt(5000, 2, 1000, mut_rate, 100, { {-20, 20}, {-20, 20} });
        (*method)(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        timings.push_back(duration<double>(end - start).count());
    }

    return timings;
}

vector<double> testing::testShrinkRate(std::unique_ptr<AIS> method)
{
    vector<double> numbers = { 10, 50, 100, 500, 1000 };
    vector<double> timings;

    for (double& shrink_rate : numbers) {
        Options opt(5000, 2, 1000, 100, shrink_rate, { {-20, 20}, {-20, 20} });
        (*method)(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        timings.push_back(duration<double>(end - start).count());
    }

    return timings;
}
