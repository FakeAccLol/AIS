#include "myutils.h"
#include <numeric>
#include <functional>

double functions::griewank(vector<double> x)
{
    return 1 + std::inner_product(x.begin(), x.end(), x.begin(), 0) / 4000.0 -
        std::accumulate(x.begin(), x.end(), 1.0,
            [i = 0](double acc, double x) mutable {
                double result = cos(x / sqrt(++i));
                return acc * result;
            }
        );
}

double functions::stibtaig(vector<double> x)
{
    return std::accumulate(x.begin(), x.end(), 0.0,
        [](double acc, double val) {
            return acc + (std::pow(val, 4) - 16 * std::pow(val, 2) + 5 * val);
        }) / 2.0;
}

int gray::intToGray(int num) {
    return num ^ (num >> 1);
}

int gray::grayToInt(int gray) {
    unsigned int g = gray;
    unsigned int num = g;
    while (g >>= 1) {
        num ^= g;
    }
    return num;
}

vector<double> numpy::linspace(double start, double end, int num)
{
    if (num < 2)
        throw std::exception();

    std::vector<double> points;

    double step = (end - start) / (num - 1);

    points.push_back(start);
    for (int i = 1; i < num - 1; i++)
        points.push_back(start + i * step);
    points.push_back(end);

    return points;
}

vector<double> numpy::logspace(double start, double end, int num)
{
    // Проверка корректности входных данных
    if (num < 2 || start < 0)
        return { 1 };

    std::vector<double> points;

    double logStart = std::log10(start);
    double logEnd = std::log10(end);

    double step = (logEnd - logStart) / (num - 1);

    points.push_back(start);

    for (int i = 1; i < num - 1;)
        points.push_back(std::pow(10, logStart + i++ * step));

    points.push_back(end);

    return points;
}
