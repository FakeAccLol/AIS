#include "gtest/gtest.h"
#include "Antibody.h"
#include "Simulator.h"
#include <vector>
#include <algorithm>

// Тесты для класса Antibody
TEST(AntibodyTest, ConstructorInitializesCorrectly) {
    const size_t dimensions = 3;
    Antibody antibody(dimensions);
    
    // Проверяем, что позиция инициализирована правильно
    EXPECT_EQ(antibody.position.size(), dimensions);
    
    // Проверяем, что все координаты в допустимом диапазоне [-20, 20]
    for (const auto& coord : antibody.position) {
        EXPECT_GE(coord, -20.0);
        EXPECT_LE(coord, 20.0);
    }
    
    // Проверяем, что аффинность рассчитана
    EXPECT_GE(antibody.affinity, 0.0);
}

TEST(AntibodyTest, GriewankFunctionCalculation) {
    std::vector<double> test_point1 = {0.0, 0.0};
    EXPECT_DOUBLE_EQ(Antibody::griewank(test_point1), 0.0);
    
    std::vector<double> test_point2 = {1.0, 1.0};
    double expected_value = 1 + (1+1)/4000.0 - cos(1.0)*cos(1.0/sqrt(2.0));
    EXPECT_DOUBLE_EQ(Antibody::griewank(test_point2), expected_value);
}

TEST(AntibodyTest, MutationChangesPosition) {
    const size_t dimensions = 2;
    Antibody antibody(dimensions);
    std::vector<double> original_position = antibody.position;
    double original_affinity = antibody.affinity;
    
    antibody.mutate(1.0); // Мутация с малым коэффициентом
    
    // Проверяем, что позиция изменилась
    EXPECT_NE(antibody.position, original_position);
    
    // Проверяем, что аффинность пересчитана
    EXPECT_NE(antibody.affinity, original_affinity);
    
    // Проверяем, что изменения в пределах mutation rate
    for (size_t i = 0; i < dimensions; ++i) {
        EXPECT_NEAR(antibody.position[i], original_position[i], 1.0);
    }
}

// Тесты для класса Simulator
TEST(SimulatorTest, PopulationInitialization) {
    Simulator::SimulatorOptions opt;
    opt.population_size = 100;
    opt.dimensions = 2;
    
    Simulator simulator;
    std::vector<Antibody> population;
    
    // Проверяем инициализацию популяции
    for (size_t i = 0; i < opt.population_size; ++i) {
        population.emplace_back(opt.dimensions);
    }
    
    EXPECT_EQ(population.size(), opt.population_size);
    for (const auto& antibody : population) {
        EXPECT_EQ(antibody.position.size(), opt.dimensions);
    }
}

TEST(SimulatorTest, PopulationSorting) {
    std::vector<Antibody> population;
    population.emplace_back(2); // Создаем несколько антител
    population.emplace_back(2);
    population.emplace_back(2);
    
    // Меняем аффинности для теста
    population[0].affinity = 5.0;
    population[1].affinity = 3.0;
    population[2].affinity = 1.0;
    
    // Сортируем
    std::sort(population.begin(), population.end(), [](const Antibody& a, const Antibody& b) {
        return a.affinity < b.affinity;
    });
    
    // Проверяем порядок
    EXPECT_DOUBLE_EQ(population[0].affinity, 1.0);
    EXPECT_DOUBLE_EQ(population[1].affinity, 3.0);
    EXPECT_DOUBLE_EQ(population[2].affinity, 5.0);
}

TEST(SimulatorTest, FullAlgorithmRun) {
    Simulator simulator;
    Simulator::SimulatorOptions opt;
    opt.population_size = 50;
    opt.dimensions = 2;
    opt.generations = 10;
    opt.mutation_rate = 1.0;
    opt.shrick_rate = 10;
    
    // Запускаем алгоритм
    simulator(opt);
    
    // Этот тест в основном проверяет, что алгоритм выполняется без ошибок
    // Более сложные проверки потребуют модификации кода для тестирования
    SUCCEED();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}