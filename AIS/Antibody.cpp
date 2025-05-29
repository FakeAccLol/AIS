#include "Antibody.h"


double Antibody::griewank(const std::vector<double>& x) {
	return 1 + std::inner_product(x.begin(), x.end(), x.begin(), 0) / 4000.0 -
		// Prod
		std::accumulate(x.begin(), x.end(), 1.0,
			[i = 0](double acc, double x) mutable {
				double result = cos(x / sqrt(++i));
				return acc * result;
			}
		);
}

double Antibody::stibtaig(const std::vector<double>& x) {
	return std::accumulate(x.begin(), x.end(), 0.0,
		[](double acc, double val) {
			return acc + (std::pow(val, 4) - 16 * std::pow(val, 2) + 5 * val);
		}) / 2.0;
}

// Определяем без значения по умолчанию тута
Antibody::Antibody(size_t dim, std::pair<double, double> limits) : position(dim), gen(std::random_device()()) {
	std::uniform_real_distribution<> dis(limits.first, limits.second);

	for (auto& x : position)
		x = dis(gen);

	affinity = stibtaig(position);
}

double Antibody::operator()(double rate) {
	mutate(rate);
	return affinity;
}

void Antibody::mutate(double rate) {
	// TODO add grey 
	/*int n = 10000;
	double h = 2 * rate / n;*/
	

	std::uniform_real_distribution<> dis(-rate, rate);

	for (auto& x : position)
		//double x0 = x - rate;
		x += dis(gen);

	affinity = stibtaig(position);
}


double Antibody::call_foo(const std::vector<double>& x) {
	return stibtaig(x);
}
