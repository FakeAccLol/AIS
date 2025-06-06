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

testing::Return testing::testPopulationSize(std::shared_ptr<AIS> method)
{
    testing::Return returninfo;
    vector<size_t> numbers = { 100, 1000, 10000, 100000, 1000000 };
    vector<double> timings;
    Options opt(1000, 2, 1000, 100, 100, 10, { {-20, 20}, {-20, 20} });
    opt.eps = 0.001;
    for (size_t& pop_size : numbers) {

        opt.population_size = pop_size;

        method->setOpt(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        returninfo.timeStamps.push_back(duration<double>(end - start).count());
        returninfo.calls.push_back(method->calls);
        returninfo.info.push_back(method->info);
    }
    return returninfo;
}

testing::Return testing::testDimSize(std::shared_ptr<AIS> method)
{
    testing::Return returninfo;
    vector<size_t> numbers = { 2, 5, 10, 15, 20 };
    vector<double> timings;
    Options opt(1000, 2, 1000, 100, 100, 10, { {-20, 20}, {-20, 20} });
    opt.eps = 0.001;
    for (size_t& dim_size : numbers) {
        vector<pair<double, double>> bounds;
        for (size_t i = 0; i < dim_size; ++i)
            bounds.push_back({ -20, 20 });
        opt.search_area = bounds;
        opt.dimensions = dim_size;
        method->setOpt(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        returninfo.timeStamps.push_back(duration<double>(end - start).count());
        returninfo.calls.push_back(method->calls);
        returninfo.info.push_back(method->info);
    }
    return returninfo;
}

testing::Return testing::testGenAmount(std::shared_ptr<AIS> method)
{
    testing::Return returninfo;
    vector<size_t> numbers = { 50, 100, 500, 1000, 5000, 10000 };
    vector<double> timings;
    Options opt(1000, 2, 1000, 100, 100, 10, { {-20, 20}, {-20, 20} });
    opt.eps = 0.001;
    for (size_t& gens : numbers) {
        opt.generations = gens;
        method->setOpt(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        returninfo.timeStamps.push_back(duration<double>(end - start).count());
        returninfo.calls.push_back(method->calls);
        returninfo.info.push_back(method->info);
    }
    return returninfo;
}

testing::Return testing::testMutationRate(std::shared_ptr<AIS> method)
{
    testing::Return returninfo;
    vector<size_t> numbers = { 100, 500, 1000, 5000, 15000, 30000 };
    vector<double> timings;
    Options opt(1000, 2, 1000, 100, 100, 10, { {-20, 20}, {-20, 20} });
    opt.eps = 0.001;
    for (auto& mut_rate : numbers) {
        opt.mutation_rate = mut_rate;
        method->setOpt(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        returninfo.timeStamps.push_back(duration<double>(end - start).count());
        returninfo.calls.push_back(method->calls);
        returninfo.info.push_back(method->info);
    }
    return returninfo;
}

testing::Return testing::testShrinkRate(std::shared_ptr<AIS> method)
{
    testing::Return returninfo;
    vector<double> numbers = { 10, 50, 100, 500, 1000 };
    vector<double> timings;
    Options opt(1000, 2, 1000, 100, 100, 10, { {-20, 20}, {-20, 20} });
    opt.eps = 0.001;
    for (double& shrink_rate : numbers) {
        opt.shrick_rate = shrink_rate;
        method->setOpt(opt);

        auto start = high_resolution_clock::now();
        method->run();
        auto end = high_resolution_clock::now();

        returninfo.timeStamps.push_back(duration<double>(end - start).count());
        returninfo.calls.push_back(method->calls);
        returninfo.info.push_back(method->info);
    }
    return returninfo;
}
