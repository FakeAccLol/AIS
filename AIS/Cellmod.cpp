#include "Cellmod.h"
#include "myutils.h"

Cellmod::Cellmod(size_t dim, function<double(vector<double>x)> f, vector<pair<double, double>> bounds) : Cell(dim, f, bounds)
{

}

void Cellmod::mutate(int rate)
{
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
