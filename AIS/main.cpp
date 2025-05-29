#include "testing.h"
#include <iostream>
#include <memory>
#include <vector>

// Базовый класс AIS
class AIS {
public:
    virtual ~AIS() = default;
    virtual void optimize() = 0;  // Основной метод
    virtual void specialFunction() {}  // Дополнительный метод для AISbase2
};

// Первая реализация AISbase
class AISbase : public AIS {
public:
    void optimize() override {
        std::cout << "AISbase::optimize() called" << std::endl;
    }
};

// Модифицированная версия AISbase
class AISmod : public AISbase {
public:
    void optimize() override {
        std::cout << "AISmod::optimize() called" << std::endl;
    }
};

// Вторая реализация AISbase с дополнительной функцией
class AISbase2 : public AIS {
public:
    void optimize() override {
        std::cout << "AISbase2::optimize() called" << std::endl;
    }
    
    void specialFunction() override {
        std::cout << "AISbase2::specialFunction() called" << std::endl;
    }
};

int main() {
    // Создаем объекты разных реализаций
    std::vector<std::unique_ptr<AIS>> methods;
    methods.push_back(std::make_unique<AISbase>());
    methods.push_back(std::make_unique<AISmod>());
    methods.push_back(std::make_unique<AISbase2>());

    // Тестируем shrink rate для всех методов
    for (auto& method : methods) {
        testing::testShrinkRate(std::move(method));
    }

    // Создаем новые объекты для остальных тестов
    auto base = std::make_unique<AISbase>();
    auto mod = std::make_unique<AISmod>();
    auto base2 = std::make_unique<AISbase2>();

    // Выполняем остальные тесты
    testing::testPopulationSize(std::move(base));
    testing::testDimSize(std::move(mod));
    testing::testMutationRate(std::move(base2));
    
    return 0;
}
