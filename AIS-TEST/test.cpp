#include "pch.h"
#include "../AIS/Antibody.h"
#include "../AIS/Antibody.cpp"
#include "../AIS/Simulator.h"
#include "../AIS/Simulator.cpp"
#include <vector>
#include <algorithm>

// Тесты для класса Antibody
TEST(AntibodyTest, ConstructorInitializesCorrectly) {
    const size_t dimensions = 3;
    std::pair<double, double> limits = { -10.0, 10.0 };
    Antibody antibody(dimensions, limits);

    // Проверяем инициализацию позиции
    EXPECT_EQ(antibody.position.size(), dimensions);

    // Проверяем границы значений
    for (const auto& coord : antibody.position) {
        EXPECT_GE(coord, limits.first);
        EXPECT_LE(coord, limits.second);
    }

    // Проверяем расчет аффинности
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

    antibody.mutate(0.5); // Мутация с коэффициентом 0.5

    // Проверяем изменения позиции
    EXPECT_NE(antibody.position, original_position);

    // Проверяем пересчет аффинности
    EXPECT_NE(antibody.affinity, original_affinity);

    // Проверяем диапазон изменений
    for (size_t i = 0; i < dimensions; ++i) {
        EXPECT_NEAR(antibody.position[i], original_position[i], 0.5);
    }
}

TEST(AntibodyTest, FunctionCallOperator) {
    const size_t dimensions = 2;
    Antibody antibody(dimensions, { -1.0, 1.0 });
    double original_affinity = antibody.affinity;

    // Используем оператор () для мутации и получения аффинности
    double new_affinity = antibody(0.1);

    // Проверяем, что аффинность изменилась
    EXPECT_NE(new_affinity, original_affinity);

    // Проверяем, что operator() возвращает текущую аффинность
    EXPECT_DOUBLE_EQ(new_affinity, antibody.affinity);
}

// Тесты для класса Simulator
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

    // Проверяем размер популяции
    EXPECT_EQ(population.size(), opt.population_size);

    // Проверяем размерность каждого антитела
    for (const auto& antibody : population) {
        EXPECT_EQ(antibody.position.size(), opt.dimensions);

        // Проверяем границы значений
        for (const auto& coord : antibody.position) {
            EXPECT_GE(coord, opt.search_area.first);
            EXPECT_LE(coord, opt.search_area.second);
        }
    }
}

TEST(SimulatorTest, PopulationSorting) {
    Simulator simulator;
    auto& population = const_cast<std::vector<Antibody>&>(simulator.getPopulation());

    // Создаем тестовые антитела
    population.emplace_back(2, std::make_pair(-1.0, 1.0));
    population.emplace_back(2, std::make_pair(-1.0, 1.0));
    population.emplace_back(2, std::make_pair(-1.0, 1.0));

    // Устанавливаем тестовые аффинности
    population[0].affinity = 5.0;
    population[1].affinity = 3.0;
    population[2].affinity = 1.0;

    // Сортируем
    std::sort(population.begin(), population.end(), [](const Antibody& a, const Antibody& b) {
        return a.affinity < b.affinity;
        });

    // Проверяем порядок сортировки
    EXPECT_DOUBLE_EQ(population[0].affinity, 1.0);
    EXPECT_DOUBLE_EQ(population[1].affinity, 3.0);
    EXPECT_DOUBLE_EQ(population[2].affinity, 5.0);
}

TEST(SimulatorTest, FullAlgorithmRunImprovesSolution) {
    Simulator simulator;
    Simulator::SimulatorOptions opt;
    opt.population_size = 50;
    opt.dimensions = 2;
    opt.generations = 5;  // Уменьшено для быстрого тестирования
    opt.mutation_rate = 1.0;
    opt.shrick_rate = 10;
    opt.search_area = { -10.0, 10.0 };

    // Запускаем алгоритм
    simulator(opt);

    const auto& population = simulator.getPopulation();

    // Проверяем, что популяция не пуста
    ASSERT_FALSE(population.empty());

    // Проверяем, что лучшее решение имеет разумное значение аффинности
    EXPECT_LT(population[0].affinity, 1.0); // Ожидаем, что найдено решение лучше 1.0

    // Проверяем, что координаты в заданных пределах
    for (const auto& coord : population[0].position) {
        EXPECT_GE(coord, opt.search_area.first);
        EXPECT_LE(coord, opt.search_area.second);
    }
}

