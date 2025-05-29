#include "Cellbase.h"
#include "myutils.h"

Cellbase::Cellbase(size_t dim, function<double(vector<double> x)> f, vector<pair<double, double>> bounds) : Cell(dim, f, bounds)
{

}

std::unique_ptr<Cellbase> Cellbase::clone() const
{
	return std::make_unique<Cellbase>(*this);
}

void Cellbase::mutate(int rate)
{
	if (rate < 0)
		rate *= -1;
	std::uniform_int_distribution dis(-rate, rate);

	for (size_t i = 0; i < position.size(); ++i) {
		int val = 32000 * (position[i] - bounds[i].first) / (bounds[i].second - bounds[i].first);
		int gray = gray::intToGray(val);
		gray += dis(gen);
		val = gray::grayToInt(gray);
		position[i] = bounds[i].first + val * (bounds[i].second - bounds[i].first) / 32000;
	}
	affinity = foo(position);
}
