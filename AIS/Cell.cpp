#include "Cell.h"

Cell::Cell(size_t dim, function<double(vector<double> x)> f, vector<pair<double, double>> bounds) : position(dim), gen(std::random_device()()), affinity(std::numeric_limits<double>::infinity()), foo(f), bounds(bounds) {
	if (bounds.size() != dim - 1)
		throw 53;
	for (size_t i = 0; i < dim; ++i) {
		std::uniform_real_distribution<> dis(bounds[i].first, bounds[i].second);
		position[i] = dis(gen);
	}

	affinity = foo(position);
}

double Cell::operator()(int rate)
{
	mutate(rate);
	return affinity;
}
