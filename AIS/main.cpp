#include "testing.h"
#include "myutils.h"

#include <iostream>
#include <memory>
#include <fstream>;
#include <vector>

using std::cout;
using std::endl;

int main() {
    std::ofstream out("tests.csv");
    // Создаем объекты разных реализаций
    Options def;
    std::vector<std::shared_ptr<AIS>> methods;
    methods.emplace_back(std::make_shared<AISbase>(def));
    methods.emplace_back(std::make_shared<AISmod>(def));
    methods.emplace_back(std::make_shared<AISmod>(def));
    methods[0]->set_foo(functions::griewank);
    methods[1]->set_foo(functions::griewank);
    methods[2]->set_foo(functions::stibtaig);

    // Тестируем для всех методов
    for (auto& method : methods) {

        testing::Return rez1 = testing::testPopulationSize(method);
        out << "PopSize" << endl;
        out << "Time" << endl;
        for (auto& val : rez1.timeStamps)
            out << val << ';';
        out << endl;
        out << "Calls" << endl;
        for (auto& val : rez1.calls)
            out << val << ';';
        out << endl;
        out << "process" << endl;
        for (int i = 0; i < rez1.info.size(); ++i) {
            out << i << endl;
            for (auto& pai : rez1.info[i])
                out << pai.first << ';' << pai.second << endl;
            out << endl;
        }
        out << endl;
        testing::Return rez2 = testing::testDimSize(method);
        out << "DimSize" << endl;
        out << "Time" << endl;
        for (auto& val : rez2.timeStamps)
            out << val << ';';
        out << endl;
        out << "Calls" << endl;
        for (auto& val : rez2.calls)
            out << val << ';';
        out << endl;
        out << "process" << endl;
        for (int i = 0; i < rez2.info.size(); ++i) {
            out << i << endl;
            for (auto& pai : rez2.info[i])
                out << pai.first << ';' << pai.second << endl;
            out << endl;
        }
        out << endl;

        testing::Return rez3 = testing::testGenAmount(method);
        out << "GenAmount" << endl;
        out << "Time" << endl;
        for (auto& val : rez3.timeStamps)
            out << val << ';';
        out << endl;
        out << "Calls" << endl;
        for (auto& val : rez3.calls)
            out << val << ';';
        out << endl;
        out << "process" << endl;
        for (int i = 0; i < rez3.info.size(); ++i) {
            out << i << endl;
            for (auto& pai : rez3.info[i])
                out << pai.first << ';' << pai.second << endl;
            out << endl;
        }
        out << endl;

        testing::Return rez4 = testing::testMutationRate(method);
        out << "MutRate" << endl;
        out << "Time" << endl;
        for (auto& val : rez4.timeStamps)
            out << val << ';';
        out << endl;
        out << "Calls" << endl;
        for (auto& val : rez4.calls)
            out << val << ';';
        out << endl;
        out << "process" << endl;
        for (int i = 0; i < rez4.info.size(); ++i) {
            out << i << endl;
            for (auto& pai : rez4.info[i])
                out << pai.first << ';' << pai.second << endl;
            out << endl;
        }
        out << endl;

        testing::Return rez5 = testing::testShrinkRate(method);
        out << "ShrinkRate" << endl;
        out << "Time" << endl;
        for (auto& val : rez5.timeStamps)
            out << val << ';';
        out << endl;
        out << "Calls" << endl;
        for (auto& val : rez5.calls)
            out << val << ';';
        out << endl;
        out << "process" << endl;
        for (int i = 0; i < rez5.info.size(); ++i) {
            out << i << endl;
            for (auto& pai : rez5.info[i])
                out << pai.first << ';' << pai.second << endl;
            out << endl;
        }
        out << endl;
        
    }
    
    return 0;
}
