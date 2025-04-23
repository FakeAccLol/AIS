// AIS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

// Функция Гриванка
double griewank(const std::vector<double>& x) {
    double sum = 0.0;
    double prod = 1.0;
    for (size_t i = 0; i < x.size(); ++i) {
        sum += x[i] * x[i];
        prod *= cos(x[i] / sqrt(i + 1));
    }
    return 1 + sum / 4000.0 - prod;
}

// Класс антитела
class Antibody {
private:
    std::mt19937 gen;
public:
    std::vector<double> position;
    double affinity;

    Antibody(size_t dim) : position(dim), gen(std::random_device()()) {
        std::uniform_real_distribution<> dis(-20, 20);

        for (auto& x : position)
            x = dis(gen);
     
        affinity = griewank(position);
    }

    void mutate(double rate) {
        std::uniform_real_distribution<> dis(-rate, rate);

        for (auto& x : position)
            x += dis(gen);

        affinity = griewank(position);
    }
};

// Алгоритм клональной селекции
void clonal_selection(size_t pop_size, size_t dim, size_t generations, double mutation_rate, double shrink_rate = 10) {
    std::vector<Antibody> population;

    // Инициализация популяции
    for (size_t i = 0; i < pop_size; ++i) {
        population.emplace_back(dim);
    }

    // Основной цикл
    for (size_t gen = 0; gen < generations; ++gen) {
        // Сортировка по аффинности
        std::sort(population.begin(), population.end(), [](const Antibody& a, const Antibody& b) {
            return a.affinity < b.affinity;
            });

        // Клонирование лучших антител
        std::vector<Antibody> new_population;
        size_t elite_size = pop_size / 10;
        for (size_t i = 0; i < elite_size; ++i)
            new_population.push_back(population[i]);

        // Мутация клонов
        for (size_t i = elite_size; i < pop_size; ++i) {
            population[i].mutate(mutation_rate);
            new_population.push_back(population[i]);
        }

        // Обновление популяции
        population = std::move(new_population);

        // Вывод лучшего решения
        std::cout << "Generation " << gen << ": Best affinity = " << population[0].affinity << '\t';
        for (size_t i = 0; i < dim; ++i) {
            std::cout << "x" << i + 1 << " = " << population[0].position[i] << '\t';
        }
        std::cout << std::endl;
    }

    // Вывод окончательного результата
    std::cout << "\nBest solution found:" << std::endl;
    for (size_t i = 0; i < dim; ++i) {
        std::cout << "x" << i + 1 << " = " << population[0].position[i] << std::endl;
    }
    std::cout << "Function value: " << population[0].affinity << std::endl;
}

int main() {
    size_t population_size = 1000;
    size_t dimensions = 2;
    size_t generations = 1000;
    double mutation_rate = 5;
    double shrick_rate = 100;

    clonal_selection(population_size, dimensions, generations, mutation_rate, shrick_rate);

    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
