#include "testing.h"
#include "myutils.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    // Создаем объекты разных реализаций
    Options def;
    std::vector<std::unique_ptr<AIS>> methods;
    methods.push_back(std::make_unique<AISbase>(def));
    methods.push_back(std::make_unique<AISmod>(def));
    methods.push_back(std::make_unique<AISmod>(def));
    methods[0]->set_foo(functions::griewank);
    methods[1]->set_foo(functions::griewank);
    methods[2]->set_foo(functions::stibtaig);

    // Тестируем для всех методов
    for (auto& method : methods) {

        testing::testPopulationSize(std::move(method));
        testing::testDimSize(std::move(method));
        testing::testGenAmount(std::move(method));
        testing::testMutationRate(std::move(method));
        testing::testShrinkRate(std::move(method));
    }
    
    return 0;
}
