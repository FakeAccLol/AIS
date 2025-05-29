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

        testing::Return rez1 = testing::testPopulationSize(std::move(method));
        testing::Return rez2 = testing::testDimSize(std::move(method));
        testing::Return rez3 = testing::testGenAmount(std::move(method));
        testing::Return rez4 = testing::testMutationRate(std::move(method));
        testing::Return rez5 = testing::testShrinkRate(std::move(method));
    }
    
    return 0;
}
