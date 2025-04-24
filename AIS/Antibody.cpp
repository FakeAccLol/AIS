#include "Antibody.h"


double Antibody::griewank(const std::vector<double>& x) {
	double sum = 0.0;
	double prod = 1.0;
	for (size_t i = 0; i < x.size(); ++i) {
		sum += x[i] * x[i];
		prod *= cos(x[i] / sqrt(i + 1));
	}
	return 1 + sum / 4000.0 - prod;
}

Antibody::Antibody(size_t dim) : position(dim), gen(std::random_device()()) {
	std::uniform_real_distribution<> dis(-20, 20);

	for (auto& x : position)
		x = dis(gen);

	affinity = griewank(position);
}

void Antibody::mutate(double rate) {
	std::uniform_real_distribution<> dis(-rate, rate);

	for (auto& x : position)
		x += dis(gen);

	affinity = griewank(position);
}