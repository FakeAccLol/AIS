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
	std::uniform_int_distribution dis(0, rate);

	for (size_t i = 0; i < position.size(); ++i) {
		int val = 32000 * (position[i] - bounds[i].first) / (bounds[i].second - bounds[i].first);
		unsigned int gray = gray::intToGray(val);
		if (gray > 1000000)
			throw _EXCEPTION_;

		int addval = dis(gen);
		if (gray + addval > 32000)
			gray = 32000;
		if (gray + addval < 0)
			gray = 0;
		else
			gray += dis(gen);
		int otherval = gray::grayToInt(gray);
		if (otherval > 32000)
			otherval = 32000;
		position[i] = bounds[i].first + otherval * (bounds[i].second - bounds[i].first) / 32000;
		if (position[i] < -1000)
			throw _EXCEPTION_;
	}
	affinity = foo(position);
}
