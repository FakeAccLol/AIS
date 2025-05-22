#include "pch.h"
#include "../AIS/Antibody.h"
#include "../AIS/Antibody.cpp"
#include "../AIS/Simulator.h"
#include "../AIS/Simulator.cpp"
#include <vector>
#include <algorithm>

// ����� ��� ������ Antibody
TEST(AntibodyTest, ConstructorInitializesCorrectly) {
    const size_t dimensions = 3;
    std::pair<double, double> limits = { -10.0, 10.0 };
    Antibody antibody(dimensions, limits);

    // ��������� ������������� �������
    EXPECT_EQ(antibody.position.size(), dimensions);

    // ��������� ������� ��������
    for (const auto& coord : antibody.position) {
        EXPECT_GE(coord, limits.first);
        EXPECT_LE(coord, limits.second);
    }

    // ��������� ������ ����������
    EXPECT_GE(antibody.affinity, 0.0);
}

TEST(AntibodyTest, GriewankFunctionCalculation) {
    std::vector<double> test_point1 = { 0.0, 0.0 };
    Antibody subj(2);
    EXPECT_DOUBLE_EQ(subj.call_foo(test_point1), 0.0);

    std::vector<double> test_point2 = { 1.0, 1.0 };
    double expected_value = 1 + (1 + 1) / 4000.0 - cos(1.0) * cos(1.0 / sqrt(2.0));
    EXPECT_DOUBLE_EQ(subj.call_foo(test_point2), expected_value);
}

TEST(AntibodyTest, MutationChangesPosition) {
    const size_t dimensions = 2;
    Antibody antibody(dimensions, { -5.0, 5.0 });
    std::vector<double> original_position = antibody.position;
    double original_affinity = antibody.affinity;

    antibody.mutate(0.5); // ������� � ������������� 0.5

    // ��������� ��������� �������
    EXPECT_NE(antibody.position, original_position);

    // ��������� �������� ����������
    EXPECT_NE(antibody.affinity, original_affinity);

    // ��������� �������� ���������
    for (size_t i = 0; i < dimensions; ++i) {
        EXPECT_NEAR(antibody.position[i], original_position[i], 0.5);
    }
}

TEST(AntibodyTest, FunctionCallOperator) {
    const size_t dimensions = 2;
    Antibody antibody(dimensions, { -1.0, 1.0 });
    double original_affinity = antibody.affinity;

    // ���������� �������� () ��� ������� � ��������� ����������
    double new_affinity = antibody(0.1);

    // ���������, ��� ���������� ����������
    EXPECT_NE(new_affinity, original_affinity);

    // ���������, ��� operator() ���������� ������� ����������
    EXPECT_DOUBLE_EQ(new_affinity, antibody.affinity);
}

// ����� ��� ������ Simulator
TEST(SimulatorTest, PopulationInitialization) {
    Simulator::SimulatorOptions opt;
    opt.population_size = 1000;
    opt.dimensions = 2;
    opt.search_area = { -15.0, 15.0 };
    opt.shrick_rate = 100;
    opt.generations = 1000;
    opt.mutation_rate = 2;

    Simulator simulator;
    simulator(opt);

    const auto& population = simulator.getPopulation();

    // ��������� ������ ���������
    EXPECT_EQ(population.size(), opt.population_size);

    // ��������� ����������� ������� ��������
    for (const auto& antibody : population) {
        EXPECT_EQ(antibody.position.size(), opt.dimensions);

        // ��������� ������� ��������
        for (const auto& coord : antibody.position) {
            EXPECT_GE(coord, opt.search_area.first);
            EXPECT_LE(coord, opt.search_area.second);
        }
    }
}

TEST(SimulatorTest, PopulationSorting) {
    Simulator simulator;
    auto& population = const_cast<std::vector<Antibody>&>(simulator.getPopulation());

    // ������� �������� ��������
    population.emplace_back(2, std::make_pair(-1.0, 1.0));
    population.emplace_back(2, std::make_pair(-1.0, 1.0));
    population.emplace_back(2, std::make_pair(-1.0, 1.0));

    // ������������� �������� ����������
    population[0].affinity = 5.0;
    population[1].affinity = 3.0;
    population[2].affinity = 1.0;

    // ���������
    std::sort(population.begin(), population.end(), [](const Antibody& a, const Antibody& b) {
        return a.affinity < b.affinity;
        });

    // ��������� ������� ����������
    EXPECT_DOUBLE_EQ(population[0].affinity, 1.0);
    EXPECT_DOUBLE_EQ(population[1].affinity, 3.0);
    EXPECT_DOUBLE_EQ(population[2].affinity, 5.0);
}

TEST(SimulatorTest, FullAlgorithmRunImprovesSolution) {
    Simulator simulator;
    Simulator::SimulatorOptions opt;
    opt.population_size = 50;
    opt.dimensions = 2;
    opt.generations = 5;  // ��������� ��� �������� ������������
    opt.mutation_rate = 1.0;
    opt.shrick_rate = 10;
    opt.search_area = { -10.0, 10.0 };

    // ��������� ��������
    simulator(opt);

    const auto& population = simulator.getPopulation();

    // ���������, ��� ��������� �� �����
    ASSERT_FALSE(population.empty());

    // ���������, ��� ������ ������� ����� �������� �������� ����������
    EXPECT_LT(population[0].affinity, 1.0); // �������, ��� ������� ������� ����� 1.0

    // ���������, ��� ���������� � �������� ��������
    for (const auto& coord : population[0].position) {
        EXPECT_GE(coord, opt.search_area.first);
        EXPECT_LE(coord, opt.search_area.second);
    }
}

