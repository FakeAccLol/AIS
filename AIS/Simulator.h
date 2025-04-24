#pragma once
#include "Antibody.h"
#include <iostream>

class Simulator
{
public:

    // �������� ���������� ��������
    void operator()(size_t pop_size, size_t dim, size_t generations, double mutation_rate, double shrink_rate = 10) {
        std::vector<Antibody> population;

        // ������������� ���������
        for (size_t i = 0; i < pop_size; ++i) {
            population.emplace_back(dim);
        }

        // �������� ����
        for (size_t gen = 0; gen < generations; ++gen) {
            // ���������� �� ����������
            std::sort(population.begin(), population.end(), [](const Antibody& a, const Antibody& b) {
                return a.affinity < b.affinity;
                });

            // ������������ ������ �������
            std::vector<Antibody> new_population;
            size_t elite_size = pop_size / 10;
            for (size_t i = 0; i < elite_size; ++i)
                new_population.push_back(population[i]);

            // ������� ������
            for (size_t i = elite_size; i < pop_size; ++i) {
                population[i].mutate(mutation_rate);
                new_population.push_back(population[i]);
            }

            // ���������� ���������
            population = std::move(new_population);

            // ����� ������� �������
            std::cout << "Generation " << gen << ": Best affinity = " << population[0].affinity << '\t';
            for (size_t i = 0; i < dim; ++i) {
                std::cout << "x" << i + 1 << " = " << population[0].position[i] << '\t';
            }
            std::cout << std::endl;
        }

        // ����� �������������� ����������
        std::cout << "\nBest solution found:" << std::endl;
        for (size_t i = 0; i < dim; ++i) {
            std::cout << "x" << i + 1 << " = " << population[0].position[i] << std::endl;
        }
        std::cout << "Function value: " << population[0].affinity << std::endl;
    }
};

