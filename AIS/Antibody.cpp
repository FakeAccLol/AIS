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
// Определяем без значения по умолчанию тута
Antibody::Antibody(size_t dim, std::pair<double, double> limits) : position(dim), gen(std::random_device()()) {
	std::uniform_real_distribution<> dis(limits.first, limits.second);

	for (auto& x : position)
		x = dis(gen);

	affinity = griewank(position);
}

double Antibody::operator()(double rate) {
	mutate(rate);
	return affinity;
}

void Antibody::mutate(double rate) {
	// TODO add grey 
	std::uniform_real_distribution<> dis(-rate, rate);

	for (auto& x : position)
		x += dis(gen);

	affinity = griewank(position);
}


double Antibody::call_foo(const std::vector<double>& x) {
	return griewank(x);
}
