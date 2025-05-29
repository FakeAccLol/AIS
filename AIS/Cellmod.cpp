#include "Cellmod.h"
#include "myutils.h"

Cellmod::Cellmod(size_t dim, function<double(vector<double>x)> f, vector<pair<double, double>> bounds) : Cell(dim, f, bounds)
{

}

std::unique_ptr<Cellmod> Cellmod::clone() const
{
	return std::make_unique<Cellmod>(*this);
}

void Cellmod::mutate(int rate)
{
	std::uniform_int_distribution dis(-rate, rate);

	for (size_t i = 0; i < position.size(); ++i) {
		int val = 32000 * (position[i] - bounds[i].first) / (bounds[i].second - bounds[i].first);
		int gray = gray::intToGray(val);
		int addval = dis(gen);
		if (gray + addval > 32000)
			gray = 32000;
		if (gray + addval < 0)
			gray = 0;
		else
			gray += dis(gen);
		val = gray::grayToInt(gray);
		if (val > 32000)
			val = 32000;
		position[i] = bounds[i].first + val * (bounds[i].second - bounds[i].first) / 32000;
	}
	affinity = foo(position);
}
