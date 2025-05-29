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
// double functions::griewank(vector<double> x)
// {
// 	return 1 + std::inner_product(x.begin(), x.end(), x.begin(), 0) / 4000.0 -
// 		// Prod
// 		std::accumulate(x.begin(), x.end(), 1.0,
// 			[i = 0](double acc, double x) mutable {
// 				double result = cos(x / sqrt(++i));
// 				return acc * result;
// 			}
// 		);
// }

// double functions::stibtaig(vector<double> x)
// {
// 	return std::accumulate(x.begin(), x.end(), 0.0,
// 		[](double acc, double val) {
// 			return acc + (std::pow(val, 4) - 16 * std::pow(val, 2) + 5 * val);
// 		}) / 2.0;
// }

// int gray::intToGray(int num) {
// 	string binary = std::bitset<32>(num).to_string();

// 	size_t first_one = binary.find_first_not_of('0');
// 	if (first_one != string::npos)
// 		binary = binary.substr(first_one);

// 	string gray;
// 	gray += binary[0];

// 	for (size_t i = 1; i < binary.size(); ++i)
// 		gray += (binary[i - 1] ^ binary[i]);
// 	return stoi(gray);
// }

// int gray::grayToInt(int gray) {
// 	int result = 0;
// 	string binary = std::bitset<32>(gray).to_string();
// 	result = (binary[0] - '0');

// 	for (size_t i = 1; i < binary.size(); ++i)
// 		result = result * 2 + (result ^ (binary[i] - '0'));

// 	return result;
// }
